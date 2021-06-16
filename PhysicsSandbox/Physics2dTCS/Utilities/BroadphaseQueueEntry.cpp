#include "Precompiled.hpp"

#include "MassComputationQueueEntry.hpp"

#include "Physics2dCore/Components/Colliders/Collider2d.hpp"
#include "Physics2dCore/Detection/Broadphase/IBroadphase2dManager.hpp"
#include "Physics2dTCS/Utilities/BroadphaseQueueEntry.hpp"
#include "Physics2dTCS/Components/Collider2dTCS.hpp"

namespace Physics2dTCS
{

//-------------------------------------------------------------------BroadphaseQueueEntry
void BroadphaseQueueEntry::Initialize(Collider2dTCS* collider)
{
  mInsert = true;
  mCollider = collider;
}

void BroadphaseQueueEntry::QueueInsert(BroadphaseLayerType::Enum layerType)
{
  MaskType mask = Physics2dCore::GetMaskFromBroadphaseLayer(layerType);
  // If any other insert was queued, swap those to removes and queue an insert
  if(mInsert != 0 && mInsert != mask)
  {
    mRemove |= mInsert;
    mUpdate = 0;
    mInsert = mask;
  }
  // If a remove was queued in the same layer then remove + insert = update
  else if(mRemove & mask)
  {
    mRemove &= ~mask;
    mUpdate |= mask;
  }
  // Otherwise just queue the insert
  else
    mInsert |= mask;
}

void BroadphaseQueueEntry::QueueUpdate(BroadphaseLayerType::Enum layerType)
{
  MaskType mask = Physics2dCore::GetMaskFromBroadphaseLayer(layerType);
  mUpdate |= mask;
}

void BroadphaseQueueEntry::QueueRemove(BroadphaseLayerType::Enum layerType)
{
  MaskType mask = Physics2dCore::GetMaskFromBroadphaseLayer(layerType);
  if(mInsert & mask)
  {
    mInsert &= ~mask;
  }
  else
    mRemove |= mask;
}

void BroadphaseQueueEntry::Update(float dt, IBroadphase2dManager* broadphase)
{
  SandboxBroadphase2d::BroadphaseData data;
  data.mClientData = mCollider->mCollider2d;
  data.mAabb = mCollider->mCollider2d->GetAabb();

  BroadphaseLayerType::Enum removeLayerId = Physics2dCore::GetBroadphaseLayerFromMask(mRemove);
  BroadphaseLayerType::Enum updateLayerId = Physics2dCore::GetBroadphaseLayerFromMask(mUpdate);
  BroadphaseLayerType::Enum insertLayerId = Physics2dCore::GetBroadphaseLayerFromMask(mInsert);
  broadphase->Process(insertLayerId, updateLayerId, removeLayerId, mKey, data);
  if(mRemove != 0)
  {
    mRemove = 0;
    mCurrentLayer = (BroadphaseLayerType::Enum )-1;
  }
  if(mUpdate != 0)
  {
    mUpdate = 0;
    mCurrentLayer = updateLayerId;
  }
  if(mInsert != 0)
  {
    mInsert = 0;
    mCurrentLayer = insertLayerId;
  }

  mQueued = false;
}

}//namespace Physics2dTCS
