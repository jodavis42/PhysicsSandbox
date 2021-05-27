#pragma once

#include "SandboxGeometryStandard.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------Circle2d
class Circle2d
{
public:
  Circle2d();
  Circle2d(const Vector2& center, float radius);

  Circle2d Transform(const Matrix3& transform) const;
  Vector2 Search(const Vector2& direction) const;

  float mRadius = 1.0f;
  Vector2 mCenter = Vector2::cZero;
};

}//namespace SandboxGeometry
