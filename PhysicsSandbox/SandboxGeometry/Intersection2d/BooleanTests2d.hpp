#pragma once

#include "SandboxGeometryStandard.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------BooleanTests2d
class BooleanTests2d
{
public:
  static bool AabbAabb(const Vector2& min0, const Vector2& max0, const Vector2& min1, const Vector2& max1);
  static bool AabbAabb(const Aabb2d& aabb0, const Aabb2d& aabb1);
  
  static bool CircleCircle(const Vector2& center0, float radius0, const Vector2& center1, float radius1);
  static bool CircleCircle(const Circle2d& circle0, const Circle2d& circle1);

  static bool Test(const Aabb2d& aabb0, const Aabb2d& aabb1);
  static bool Test(const Circle2d& circle0, const Circle2d& circle1);
};

}//namespace SandboxGeometry
