#pragma once

#include "SandboxGeometryStandard.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------PointTests2d
class PointTests2d
{
public:
  static bool PointAabb(const Vector2& point, const Vector2& aabbMin, const Vector2& aabbMax);
  static bool PointAabb(const Vector2& point, const Aabb2d& aabb);

  static bool PointCircle(const Vector2& point, const Vector2& circleCenter, float circleRadius);
  static bool PointCircle(const Vector2& point, const Circle2d& circle);

  static bool PointObb(const Vector2& point, const Vector2& obbCenter, const Matrix2& obbRotation, const Vector2 obbHalfExtents);
  static bool PointObb(const Vector2& point, const Obb2d& obb);

  static bool Test(const Vector2& point, const Aabb2d& aabb);
  static bool Test(const Vector2& point, const Circle2d& circle);
  static bool Test(const Vector2& point, const Obb2d& obb);
};

}//namespace SandboxGeometry
