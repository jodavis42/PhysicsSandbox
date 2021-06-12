#pragma once

#include "SandboxGeometryStandard.hpp"

#include "IntersectionResult2d.hpp"

#include "SandboxGeometry/Intersection2d/RayResult2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------RayTests2d
class RayTests2d
{
public:
  static IntersectionResult2d RayAabb(const Vector2& rayStart, const Vector2& rayDir, const Vector2& aabbMin, const Vector2& aabbMax, RayResult2d& result, float parallelEpsilonCheck = 0.001f);
  static IntersectionResult2d RayAabb(const Ray2d& ray, const Aabb2d& aabb, RayResult2d& result, float parallelEpsilonCheck = 0.001f);

  static IntersectionResult2d RayCircle(const Vector2& rayStart, const Vector2& rayDir, const Vector2& circleCenter, float circleRadius, RayResult2d& result);
  static IntersectionResult2d RayCircle(const Ray2d& ray, const Circle2d& circle, RayResult2d& result);

  static IntersectionResult2d RayObb(const Vector2& rayStart, const Vector2& rayDir, const Vector2& obbCenter, const Matrix2& obbRotation, const Vector2& obbHalfExtents, RayResult2d& result);
  static IntersectionResult2d RayObb(const Ray2d& ray, const Obb2d& obb, RayResult2d& result);
};

}//namespace SandboxGeometry
