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
  return Search(direction, mCenter, mRotation, mHalfExtents);
}

Vector2 Obb2d::Search(const Vector2& direction, const Vector2& center, const Matrix2& rotation, const Vector2& halfExtents)
{
  Matrix2 invRotation = rotation.Transposed();
  Vector2 localDirection = Math::Multiply(invRotation, direction);

  Vector2 result = Vector2::cZero;
  result[0] += Math::Sign(direction[0]) * halfExtents[0];
  result[1] += Math::Sign(direction[1]) * halfExtents[1];
  result = Math::Multiply(rotation, result) + center;
  return result;
}

}//namespace SandboxGeometry
