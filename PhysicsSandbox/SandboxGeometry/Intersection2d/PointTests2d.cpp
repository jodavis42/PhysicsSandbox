#include "Precompiled.hpp"

#include "PointTests2d.hpp"

#include "SandboxGeometry/Shapes2d/Aabb2d.hpp"
#include "SandboxGeometry/Shapes2d/Circle2d.hpp"
#include "SandboxGeometry/Shapes2d/Obb2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------PointTests2d
bool PointTests2d::PointAabb(const Vector2& point, const Vector2& aabbMin, const Vector2& aabbMax)
{
  bool xAxis = aabbMin[0] <= point[0] && point[0] <= aabbMax[0];
  bool yAxis = aabbMin[1] <= point[1] && point[1] <= aabbMax[1];
  bool result = xAxis && yAxis;
  return result;
}

bool PointTests2d::PointAabb(const Vector2& point, const Aabb2d& aabb)
{
  return PointAabb(point, aabb.mMin, aabb.mMax);
}

bool PointTests2d::PointCircle(const Vector2& point, const Vector2& circleCenter, float circleRadius)
{
  float distanceSq = Math::DistanceSq(point, circleCenter);
  float radiusSq = Math::Sq(circleRadius);
  return distanceSq <= radiusSq;
}

bool PointTests2d::PointCircle(const Vector2& point, const Circle2d& circle)
{
  return PointCircle(point, circle.mCenter, circle.mRadius);
}

bool PointTests2d::PointObb(const Vector2& point, const Vector2& obbCenter, const Matrix2& obbRotation, const Vector2 obbHalfExtents)
{
  Matrix2 invRotation = obbRotation.Transposed();
  Vector2 localPoint = Math::Multiply(invRotation, point - obbCenter);
  Vector2 aabbMin = -obbHalfExtents;
  Vector2 aabbMax = obbHalfExtents;
  return PointAabb(localPoint, aabbMin, aabbMax);
}

bool PointTests2d::PointObb(const Vector2& point, const Obb2d& obb)
{
  return PointObb(point, obb.mCenter, obb.mRotation, obb.mHalfExtents);
}

bool PointTests2d::Test(const Vector2& point, const Aabb2d& aabb)
{
  return PointAabb(point, aabb);
}

bool PointTests2d::Test(const Vector2& point, const Circle2d& circle)
{
  return PointCircle(point, circle);
}

bool PointTests2d::Test(const Vector2& point, const Obb2d& obb)
{
  return PointObb(point, obb);
}

} //namespace SandboxGeometry
