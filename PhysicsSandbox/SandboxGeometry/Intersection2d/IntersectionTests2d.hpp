#pragma once

#include "SandboxGeometryStandard.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------IntersectionTests2d
class IntersectionTests2d
{
public:
  static bool PointAabb(const Vector2& point, const Vector2& aabbMin, const Vector2& aabbMax, Manifold2d& manifold);
  static bool PointAabb(const Vector2& point, const Aabb2d& aabb, Manifold2d& manifold);
  
  static bool PointCircle(const Vector2& point, const Vector2& circleCenter, float circleRadius, Manifold2d& manifold);
  static bool PointCircle(const Vector2& point, const Circle2d& circle, Manifold2d& manifold);

  static bool AabbCircle(const Vector2& aabbMin, const Vector2& aabbMax, const Vector2& circleCenter, float circleRadius, Manifold2d& manifold);
  static bool AabbCircle(const Aabb2d& aabb, const Circle2d& circle, Manifold2d& manifold);

  static bool CircleCircle(const Vector2& center0, float radius0, const Vector2& center1, float radius1, Manifold2d& manifold);
  static bool CircleCircle(const Circle2d& circle0, const Circle2d& circle1, Manifold2d& manifold);

  static bool ObbCircle(const Vector2& obbCenter, const Matrix2& obbRotation, const Vector2 obbHalfExtents, const Vector2& circleCenter, float circleRadius, Manifold2d& manifold);
  static bool ObbCircle(const Obb2d& obb, const Circle2d& circle, Manifold2d& manifold);
  
  static bool Test(const Circle2d& circle0, const Circle2d& circle1, Manifold2d& manifold);
  static bool Test(const Obb2d& obb, const Circle2d& circle, Manifold2d& manifold);
  static bool Test(const Circle2d& circle, const Obb2d& obb, Manifold2d& manifold);
  static bool Test(const Obb2d& obb0, const Obb2d& obb1, Manifold2d& manifold);
};

}//namespace SandboxGeometry
