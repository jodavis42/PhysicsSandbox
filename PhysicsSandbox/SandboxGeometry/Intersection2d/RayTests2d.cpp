#include "Precompiled.hpp"

#include "RayTests2d.hpp"

#include "SandboxGeometry/Shapes2d/Ray2d.hpp"
#include "SandboxGeometry/Shapes2d/Aabb2d.hpp"
#include "SandboxGeometry/Shapes2d/Circle2d.hpp"
#include "SandboxGeometry/Shapes2d/Obb2d.hpp"
#include "SandboxGeometry/Intersection2d/RayResult2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------RayTests2d
IntersectionResult2d RayTests2d::RayAabb(const Vector2& rayStart, const Vector2& rayDir, const Vector2& aabbMin, const Vector2& aabbMax, RayResult2d& result, float parallelEpsilonCheck)
{
  // p = s + dt
  // Dot(n, p - p0) = 0
  // Dot(n, s + dt - p0) = 0
  // Dot(n, (s - p0)+ dt) = 0
  // Dot(n, s - p0) + Dot(n, d) * t = 0
  // t = -Dot(n, s - p0) / Dot(n, d)
  // t = -(s_i - p0_i) / d_i
  // t = (p0_i - s_i) / d_i
  float times[2] = {0, Math::PositiveMax()};
  size_t axes[2] = {0, 0};
  for(size_t axis = 0; axis < 2; ++axis)
  {
    float denom = rayDir[axis];
    if(Math::Abs(denom) < parallelEpsilonCheck)
    {
      if(rayStart[axis] < aabbMin[axis] || aabbMax[axis] < rayStart[axis])
        return IntersectionResult2d(IntersectionResult2d::Type::None);
      continue;
    }

    float t0 = (aabbMin[axis] - rayStart[axis]) / denom;
    float t1 = (aabbMax[axis] - rayStart[axis]) / denom;
    size_t axis0 = axis * 2;
    size_t axis1 = axis * 2 + 1;
    if(denom < 0)
    {
      Math::Swap(t0, t1);
      Math::Swap(axis0, axis1);
    }
    if(t0 > times[0])
    {
      times[0] = t0;
      axes[0] = axis0;
    }
    if(t1 < times[1])
    {
      times[1] = t1;
      axes[1] = axis1;
    }

    if(times[1] < times[0])
      return IntersectionResult2d(IntersectionResult2d::Type::None);
  }

  result.mPointCount = 2;
  for(size_t i = 0; i < result.mPointCount; ++i)
  {
    RayIntersectionPoint2d& point = result.mPoints[i];
    point.mTime = times[i];
    point.mPoint = rayStart + rayDir * point.mTime;
    point.mNormal = Vector2::cZero;
    point.mNormal[axes[i] / 2] = axes[i] % 2 ? -1.0f : 1.0f;
  }

  return IntersectionResult2d(IntersectionResult2d::Type::Hit);
}

IntersectionResult2d RayTests2d::RayAabb(const Ray2d& ray, const Aabb2d& aabb, RayResult2d& result, float parallelEpsilonCheck)
{
  return RayAabb(ray.mStart, ray.mDirection, aabb.mMin, aabb.mMax, result, parallelEpsilonCheck);
}

IntersectionResult2d RayTests2d::RayCircle(const Vector2& rayStart, const Vector2& rayDir, const Vector2& circleCenter, float circleRadius, RayResult2d& result)
{
  // p = s + dt
  // (p - p0)^2 - r^2 = 0
  // (s + dt - p0)^2 - r^2 = 0
  // (m + dt)^2 - r^2 = 0
  // m^2 + 2mdt - d^2t^2 - r^2 = 0
  Vector2 m = rayStart - circleCenter;
  float a = Math::Dot(rayDir, rayDir);
  float b = 2 * Math::Dot(m, rayDir);
  float c = Math::Dot(m, m) - Math::Sq(circleRadius);
  float desc = b * b - 4 * a * c;
  if(desc < 0)
    return IntersectionResult2d(IntersectionResult2d::Type::None);

  result.mPointCount = (desc == 0) ? 1 : 2;
  float denom = 2 * a;
  float descSqrt = Math::Sqrt(desc);

  float times[2];
  times[0] = (-b - descSqrt) / denom;
  times[1] = (-b + descSqrt) / denom;
  // Both points are behind
  if(times[1] < 0)
    return IntersectionResult2d(IntersectionResult2d::Type::None);

  // On point is behind
  if(times[0] < 0)
  {
    result.mPointCount = 0;
    times[0] = times[1];
  }

  for(size_t i = 0; i < result.mPointCount; ++i)
  {
    RayIntersectionPoint2d& point = result.mPoints[i];
    point.mTime = times[i];
    point.mPoint = rayStart + rayDir * point.mTime;
    point.mNormal = Math::Normalized(point.mPoint - circleCenter);
  }

  return IntersectionResult2d(IntersectionResult2d::Type::Hit);
}

IntersectionResult2d RayTests2d::RayCircle(const Ray2d& ray, const Circle2d& circle, RayResult2d& result)
{
  return RayCircle(ray.mStart, ray.mDirection, circle.mCenter, circle.mRadius, result);
}

IntersectionResult2d RayTests2d::RayObb(const Vector2& rayStart, const Vector2& rayDir, const Vector2& obbCenter, const Matrix2& obbRotation, const Vector2& obbHalfExtents, RayResult2d& result)
{
  Matrix2 invRotation = obbRotation.Transposed();

  Vector2 aabbMin = obbCenter - obbHalfExtents;
  Vector2 aabbMax = obbCenter + obbHalfExtents;
  // Rotate the ray by the inverse of the obb's rotation, turning it into Ray vs Aabb
  Vector2 localRayCenter = Math::Multiply(invRotation, rayStart - obbCenter);
  Vector2 localRayDir = Math::Multiply(invRotation, rayDir);
  IntersectionResult2d intersectionResult = RayAabb(localRayCenter, localRayDir, aabbMin, aabbMax, result);
  if(intersectionResult)
    result.TransformPoints(obbRotation, obbCenter);

  return intersectionResult;
}

IntersectionResult2d RayTests2d::RayObb(const Ray2d& ray, const Obb2d& obb, RayResult2d& result)
{
  return RayObb(ray.mStart, ray.mDirection, obb.mCenter, obb.mRotation, obb.mHalfExtents, result);
}

} //namespace SandboxGeometry
