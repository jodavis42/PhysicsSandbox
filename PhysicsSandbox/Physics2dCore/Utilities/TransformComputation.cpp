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
  Vector2 localPositionOffset = body.GetCenterOfMassPositionOffset();

  Matrix2 worldRotationMatrix = Matrix2::GenerateRotation(worldRotation);
  Vector2 worldPositionOffset = Math::Multiply(worldRotationMatrix, localPositionOffset);
  Vector2 worldTranslation = worldCenterOfMass - worldPositionOffset;

  Zero::Transform* transform = body.GetOwner()->has(Zero::Transform);
  transform->SetWorldTranslationInternal(Math::ToVector3(worldTranslation, 0));
  transform->SetWorldRotationInternal(Math::ToQuaternion(Vector3(0, 0, 1), worldRotation));

  Zero::TransformUpdateInfo info;
  info.TransformFlags = Zero::TransformUpdateFlags::Physics;
  transform->TransformUpdate(info);
}

}//namespace Physics2dCore
