#include "Precompiled.hpp"

#include "MassComputationQueueEntry.hpp"

#include "Physics2dTCS/Components/RigidBody2dTCS.hpp"
#include "Physics2dCore/Utilities/MassComputation.hpp"
#include "Physics2dCore/Utilities/TransformComputation.hpp"
#include "Physics2dCore/Components/RigidBody2d.hpp"

namespace Physics2dTCS
{

//-------------------------------------------------------------------MassComputationQueueEntry
void MassComputationQueueEntry::Initialize(RigidBody2dTCS* owner)
{
  mRigidBody = owner;
  mUpdateMassProperties = true;
}

void MassComputationQueueEntry::Update(float dt)
{
  ComputeMassAndCenterOfMass();
}

void MassComputationQueueEntry::ComputeMassAndCenterOfMass()
{
  if(!mUpdateMassProperties)
    return;

  Physics2dCore::RigidBody2d* rigidBody2d = mRigidBody->mRigidBody2d;
  Array<Physics2dCore::ColliderMassProperties2d> colliderMassProperties;
  for(auto&& colliderRange = mRigidBody->mColliders.All(); !colliderRange.Empty(); colliderRange.PopFront())
  {
    auto&& collider2d = colliderRange.Front();
    colliderMassProperties.PushBack(collider2d.GetMassProperties());
  }
  Physics2dCore::MassComputation::ComputeMassProperties(*rigidBody2d, colliderMassProperties);
  Physics2dCore::TransformComputation::UpdateBodyRotation(*rigidBody2d);

  mUpdateMassProperties = false;
}

}//namespace Physics2dTCS
