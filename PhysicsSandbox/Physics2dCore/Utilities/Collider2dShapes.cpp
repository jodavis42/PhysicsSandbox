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

}//namespace Physics2dCore
