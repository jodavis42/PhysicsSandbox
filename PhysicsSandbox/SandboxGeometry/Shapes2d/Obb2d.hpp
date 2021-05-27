#pragma once

#include "SandboxGeometryStandard.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------Obb2d
class Obb2d
{
public:
  Obb2d Transform(const Matrix2& rotation) const;
  Vector2 Search(const Vector2& direction) const;

  Vector2 mCenter = Vector2::cZero;
  Vector2 mHalfExtents = Vector2(0.5f, 0.5f);
  Matrix2 mRotation = Matrix2::cIdentity;
};

}//namespace SandboxGeometry
