#include "Precompiled.hpp"

#include "Obb2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------Obb2d
Obb2d Obb2d::Transform(const Matrix2& rotation) const
{
  Obb2d result;
  result.mCenter = mCenter;
  result.mRotation = Math::Multiply(rotation, mRotation);
  result.mHalfExtents = mHalfExtents;
  return result;
}

Vector2 Obb2d::Search(const Vector2& direction) const
{
  Matrix2 invRotation = mRotation.Transposed();
  Vector2 localDirection = Math::Multiply(invRotation, direction);

  Vector2 result = Vector2::cZero;
  result[0] += Math::Sign(direction[0]) * mHalfExtents[0];
  result[1] += Math::Sign(direction[1]) * mHalfExtents[1];
  result = Math::Multiply(mRotation, result) + mCenter;
  return result;
}

}//namespace SandboxGeometry
