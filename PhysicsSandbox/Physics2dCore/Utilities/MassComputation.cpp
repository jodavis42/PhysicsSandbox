#include "Precompiled.hpp"

#include "MassComputation.hpp"

#include "Physics2dCore/Components/RigidBody2d.hpp"
#include "Physics2dCore/Components/Colliders/Collider2d.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------MassComputation
void MassComputation::ComputeMassProperties(RigidBody2d& body, const Array<ColliderMassProperties2d>& colliderMasses)
{
  Physics2dCore::BodyMassProperties2d bodyProperties;
  float totalArea = 0.0f;
  for(auto&& colliderRange = colliderMasses.All(); !colliderRange.Empty(); colliderRange.PopFront())
  {
    auto&& massProperties = colliderMasses.Front();
    totalArea += massProperties.mArea;
    bodyProperties.mCenterOfMass += massProperties.mArea * massProperties.mCenterOfMass;
  }
  if(totalArea != 0.0f)
    bodyProperties.mCenterOfMass /= totalArea;
  UpdateMassProperties(body, bodyProperties);
}

void MassComputation::UpdateMassProperties(RigidBody2d& body, const BodyMassProperties2d& bodyMassProperties)
{
  Vector2 worldTranslation = body.GetWorldTranslation();
  Matrix2 worldRotationMatrix = Matrix2::GenerateRotation(body.GetWorldRotation());
  Vector2 localTranslationOffset = Math::Multiply(worldRotationMatrix.Transposed(), worldTranslation - bodyMassProperties.mCenterOfMass);

  body.SetInvMassNoEvent(1.0f / bodyMassProperties.mMass);
  body.SetInvInertiaNoEvent(1.0f / bodyMassProperties.mInertia);
  body.SetWorldCenterOfMassNoEvent(bodyMassProperties.mCenterOfMass);
  body.SetBodyLocalTranslationOffsetNoEvent(localTranslationOffset);
}

}//namespace Physics2dCore
