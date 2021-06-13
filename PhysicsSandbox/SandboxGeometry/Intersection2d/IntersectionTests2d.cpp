#include "Precompiled.hpp"

#include "IntersectionTests2d.hpp"

#include "SandboxGeometry/Shapes2d/Aabb2d.hpp"
#include "SandboxGeometry/Shapes2d/Circle2d.hpp"
#include "SandboxGeometry/Shapes2d/Obb2d.hpp"
#include "SandboxGeometry/Intersection2d/Manifold2d.hpp"
#include "SandboxGeometry/Intersection2d/PointTests2d.hpp"

namespace SandboxGeometry
{

size_t SelectMinAxis(const Vector2& values)
{
  size_t axis = 0;
  if(values[1] < values[0])
    axis = 1;
  return axis;
}

//-------------------------------------------------------------------IntersectionTests2d
bool IntersectionTests2d::PointAabb(const Vector2& point, const Vector2& aabbMin, const Vector2& aabbMax, Manifold2d& manifold)
{
  if(!PointTests2d::PointAabb(point, aabbMin, aabbMax))
    return false;

  Vector2 aabbMinDistances = point - aabbMin;
  Vector2 aabbMaxDistances = aabbMax - point;

  size_t aabbMinIndex = SelectMinAxis(aabbMinDistances);
  size_t aabbMaxIndex = SelectMinAxis(aabbMaxDistances);

  float aabbMinDistance = aabbMinDistances[aabbMinIndex];
  float aabbMaxDistance = aabbMaxDistances[aabbMaxIndex];
  Vector2 distances(aabbMinDistance, aabbMaxDistance);
  size_t minMaxAxis = SelectMinAxis(distances);
  if(distances[minMaxAxis] < 0)
    return false;

  manifold.mPointCount = 1;
  auto&& manifoldPoint = manifold[0];
  size_t normalAxis = (minMaxAxis == 0) ? aabbMinIndex : aabbMaxIndex;
  manifoldPoint.mNormal = (normalAxis == 0) ? Vector2::cXAxis : Vector2::cYAxis;
  manifoldPoint.mNormal *= (minMaxAxis == 0) ? -1.0f : 1.0f;
 

  manifoldPoint.mPenetrationDistance = distances[minMaxAxis];
  manifoldPoint.mPoints[1] = point;
  manifoldPoint.mPoints[0] = point + manifoldPoint.mNormal * manifoldPoint.mPenetrationDistance;
  return true;
}
bool IntersectionTests2d::PointAabb(const Vector2& point, const Aabb2d& aabb, Manifold2d& manifold)
{
  return PointAabb(point, aabb.mMin, aabb.mMax, manifold);
}

bool IntersectionTests2d::PointCircle(const Vector2& point, const Vector2& circleCenter, float circleRadius, Manifold2d& manifold)
{
  Vector2 offset = point - circleCenter;
  float distSq = Math::LengthSq(offset);
  float radiusSq = Math::Sq(circleRadius);
  if(radiusSq < distSq)
    return false;

  float distance = Math::Sqrt(distSq);
  manifold.mPointCount = 1;
  auto&& manifoldPoint = manifold[0];
  manifoldPoint.mNormal = offset / distance;
  manifoldPoint.mPoints[0] = circleCenter + manifoldPoint.mNormal * circleRadius;
  manifoldPoint.mPoints[1] = point;
  manifoldPoint.mPenetrationDistance = circleRadius - distance;
  return true;
}

bool IntersectionTests2d::PointCircle(const Vector2& point, const Circle2d& circle, Manifold2d& manifold)
{
  return PointCircle(point, circle.mCenter, circle.mRadius, manifold);
}

bool IntersectionTests2d::AabbCircle(const Vector2& aabbMin, const Vector2& aabbMax, const Vector2& circleCenter, float circleRadius, Manifold2d& manifold)
{
  // Deep penetration
  if(PointAabb(circleCenter, aabbMin, aabbMax, manifold))
  {
    // Fix the point/penetration distance to be for the circle, not the point
    for(size_t i = 0; i < manifold.Size(); ++i)
    {
      auto&& point = manifold[i];
      point.mPoints[1] = circleCenter - point.mNormal * circleRadius;
      point.UpdatePenetrationDistance();
    }
    return true;
  }

  // Shallow penetration
  Vector2 closestPoint = circleCenter;
  for(size_t i = 0; i < 2; ++i)
    closestPoint[i] = Math::Clamp(closestPoint[i], aabbMin[i], aabbMax[i]);

  Vector2 offsetVec = circleCenter - closestPoint;
  float distanceSq = Math::LengthSq(offsetVec);
  float radiusSq = Math::Sq(circleRadius);
  if(distanceSq > radiusSq)
    return false;

  float distance = Math::Sqrt(distanceSq);
  manifold.mPointCount = 1;
  auto&& point = manifold[0];
  point.mNormal = offsetVec / distance;
  point.mPoints[0] = closestPoint;
  point.mPoints[1] = circleCenter - point.mNormal * circleRadius;
  point.mPenetrationDistance = circleRadius - distance;

  return true;
}

bool IntersectionTests2d::AabbCircle(const Aabb2d& aabb, const Circle2d& circle, Manifold2d& manifold)
{
  return AabbCircle(aabb.mMin, aabb.mMax, circle.mCenter, circle.mRadius, manifold);
}

bool IntersectionTests2d::CircleCircle(const Vector2& center0, float radius0, const Vector2& center1, float radius1, Manifold2d& manifold)
{
  float radiiSum = radius0 + radius1;
  float radiiSumSq = Math::Sq(radiiSum);
  Vector2 v01 = center1 - center0;
  float distSq = Math::LengthSq(v01);
  if(distSq > radiiSumSq)
    return false;

  float distance = Math::Sqrt(distSq);
  manifold.mPointCount = 1;
  ManifoldPoint2d& point = manifold.mPoints[0];
  point.mNormal = v01 / distance;
  point.mPoints[0] = center0 + radius0 * point.mNormal;
  point.mPoints[1] = center1 - radius1 * point.mNormal;
  point.mPenetrationDistance = radiiSum - distance;

  return true;
}

bool IntersectionTests2d::CircleCircle(const Circle2d& circle0, const Circle2d& circle1, Manifold2d& manifold)
{
  return CircleCircle(circle0.mCenter, circle0.mRadius, circle1.mCenter, circle1.mRadius, manifold);
}

bool IntersectionTests2d::ObbCircle(const Vector2& obbCenter, const Matrix2& obbRotation, const Vector2 obbHalfExtents, const Vector2& circleCenter, float circleRadius, Manifold2d& manifold)
{
  Matrix2 invRotation = obbRotation.Transposed();

  // Transform into the space where the obb is an aabb centered at the origin
  Vector2 aabbMin = -obbHalfExtents;
  Vector2 aabbMax = obbHalfExtents;
  Vector2 localCircleCenter = Math::Multiply(invRotation, circleCenter - obbCenter);
  bool result = AabbCircle(aabbMin, aabbMax, localCircleCenter, circleRadius, manifold);
  if(result)
    manifold.TransformPoints(obbRotation, obbCenter);

  return result;
}

bool IntersectionTests2d::ObbCircle(const Obb2d& obb, const Circle2d& circle, Manifold2d& manifold)
{
  return ObbCircle(obb.mCenter, obb.mRotation, obb.mHalfExtents, circle.mCenter, circle.mRadius, manifold);
}

bool IntersectionTests2d::Test(const Circle2d& circle0, const Circle2d& circle1, Manifold2d& manifold)
{
  return CircleCircle(circle0, circle1, manifold);
}

bool IntersectionTests2d::Test(const Obb2d& obb, const Circle2d& circle, Manifold2d& manifold)
{
  return ObbCircle(obb, circle, manifold);
}

bool IntersectionTests2d::Test(const Circle2d& circle, const Obb2d& obb, Manifold2d& manifold)
{
  bool result = ObbCircle(obb, circle, manifold);
  if(result)
    manifold.Flip();
  return result;
}

bool IntersectionTests2d::Test(const Obb2d& obb0, const Obb2d& obb1, Manifold2d& manifold)
{
  return false;
}

} //namespace SandboxGeometry
