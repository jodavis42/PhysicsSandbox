#include "Precompiled.hpp"

#include "TransformComputation.hpp"

#include "Physics2dCore/Components/RigidBody2d.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------TransformComputation
void TransformComputation::UpdateTransform(RigidBody2d& body)
{
  float worldRotation = body.GetWorldRotation();
  Vector2 worldCenterOfMass = body.GetWorldCenterOfMass();
  Vector2 localTranslationOffset = body.GetBodyLocalTranslationOffset();

  Matrix2 worldRotationMatrix = Matrix2::GenerateRotation(worldRotation);
  Vector2 worldPositionOffset = Math::Multiply(worldRotationMatrix, localTranslationOffset);
  Vector2 worldTranslation = worldCenterOfMass - worldPositionOffset;

  Zero::Transform* transform = body.GetOwner()->has(Zero::Transform);
  transform->SetWorldTranslationInternal(Math::ToVector3(worldTranslation, 0));
  transform->SetWorldRotationInternal(Math::ToQuaternion(Vector3(0, 0, 1), worldRotation));

  Zero::TransformUpdateInfo info;
  info.TransformFlags = Zero::TransformUpdateFlags::Physics;
  transform->TransformUpdate(info);
}

void TransformComputation::UpdateBodyRotation(RigidBody2d& body)
{
  Zero::Transform* transform = body.GetOwner()->has(Zero::Transform);
  Vector3 worldXAxis = Math::Normalized(transform->TransformNormal(Vector3::cXAxis));
  float worldRotation = Math::Angle2D(worldXAxis);
  body.SetWorldRotationNoEvent(worldRotation);
}

}//namespace Physics2dCore
