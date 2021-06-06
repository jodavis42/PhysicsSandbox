#include "Precompiled.hpp"

#include "MassComputationQueueEntry.hpp"

#include "Physics2dTCS/Utilities/BroadphaseQueueEntry.hpp"

namespace Physics2dTCS
{

//-------------------------------------------------------------------BroadphaseQueueEntry
void BroadphaseQueueEntry::Initialize(Collider2dTCS* collider)
{
  mCollider = collider;
}

void BroadphaseQueueEntry::Update(float dt)
{

}

}//namespace Physics2dTCS
