#include "Precompiled.hpp"

#include "Collider2dShapes.hpp"

#include "Physics2dCore/Components/Colliders/BoxCollider2d.hpp"
#include "Physics2dCore/Components/Colliders/CircleCollider2d.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Collider2dShapes
SandboxGeometry::Obb2d Collider2dShapes::GetShape(const BoxCollider2d& collider)
{
  Matrix4 worldTransform = collider.GetFullWorldTransform();
  Vector3 scale, translation;
  Matrix3 rotation;
  worldTransform.Decompose(&scale, &rotation, &translation);
  SandboxGeometry::Obb2d result;
  result.mCenter = Math::ToVector2(translation);
  result.mHalfExtents = Math::ToVector2(scale) * 0.5f;
  result.mRotation = Math::ToMatrix2(rotation);
  return result;
}

SandboxGeometry::Circle2d Collider2dShapes::GetShape(const CircleCollider2d& collider)
{
  Matrix4 worldTransform = collider.GetFullWorldTransform();

  SandboxGeometry::Circle2d result;
  result.mCenter = Math::ToVector2(Math::MultiplyPoint(worldTransform, Vector3::cZero));
  // To get the world radius, transform the two basic vectors on the circle's surface and pick the one that is furthest away
  Vector3 radii0 = Math::MultiplyNormal(worldTransform, Vector3(collider.GetRadius(), 0, 0));
  Vector3 radii1 = Math::MultiplyNormal(worldTransform, Vector3(0, collider.GetRadius(), 0));
  result.mRadius = Math::Sqrt(Math::Max(Math::LengthSq(radii0), Math::LengthSq(radii1)));
  return result;
}

SandboxGeometry::Aabb2d Collider2dShapes::GetAabb(const BoxCollider2d& collider)
{
  SandboxGeometry::Obb2d obb = GetShape(collider);
  
  Matrix2 absRotation;
  for(size_t axis = 0; axis < 2; ++axis)
    absRotation.SetBasis(axis, Math::Abs(absRotation.GetBasis(axis)));
  Vector2 halfExtents = Math::Multiply(absRotation, obb.mHalfExtents);
  return SandboxGeometry::Aabb2d::FromCenterAndHalfExtents(obb.mCenter, halfExtents);
}

SandboxGeometry::Aabb2d Collider2dShapes::GetAabb(const CircleCollider2d& collider)
{
  SandboxGeometry::Circle2d circle = GetShape(collider);
  return SandboxGeometry::Aabb2d::FromCenterAndHalfExtents(circle.mCenter, Vector2(circle.mRadius));
}

}//namespace Physics2dCore
