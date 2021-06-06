#include "Precompiled.hpp"

#include "MassComputationQueueEntry.hpp"

#include "Physics2dTCS/Components/RigidBody2dTCS.hpp"
#include "Physics2dCore/Utilities/MassComputation.hpp"

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

  Array<Physics2dCore::ColliderMassProperties2d> colliderMassProperties;
  for(auto&& colliderRange = mRigidBody->mColliders.All(); !colliderRange.Empty(); colliderRange.PopFront())
  {
    auto&& collider2d = colliderRange.Front();
    colliderMassProperties.PushBack(collider2d.GetMassProperties());
  }
  Physics2dCore::MassComputation::ComputeMassProperties(*mRigidBody->mRigidBody2d, colliderMassProperties);

  mUpdateMassProperties = false;
}

}//namespace Physics2dTCS
