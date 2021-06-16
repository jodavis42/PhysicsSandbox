#pragma once

#include "Physics2dStandardTCS.hpp"

#include "Physics2dTCS/Utilities/BroadphaseQueueEntry.hpp"
#include "Physics2dTCS/Utilities/MassComputationQueueEntry.hpp"
#include "Physics2dTCS/Utilities/TransformCacheQueueEntry.hpp"
#include "Physics2dTCS/Utilities/HierarchyBuildingTask.hpp"

namespace Physics2dTCS
{

//-------------------------------------------------------------------Physics2dQueues
/// Queue manager to efficiently track and update various updates that need to happen only to some objects.
/// This allows a bunch of changes to happen (size changing, mass changing, position updates, etc...) 
/// but only process them once when needed, avoiding a bunch of partial state updates.
class Physics2dQueues
{
public:
  struct UpdateContext
  {
    float mDt;
    IBroadphase2dManager* mBroadphaseManager = nullptr;
  };

  void Queue(MassComputationQueueEntry& entry);
  void Queue(BroadphaseQueueEntry& entry);
  void Queue(TransformCacheQueueEntry& entry);

  void Update(UpdateContext& context);
  void UpdateMasses(float dt);
  void UpdateBroadphase(float dt, IBroadphase2dManager* broadphase);
  void UpdateTransformCache(float dt);

  InList<TransformCacheQueueEntry, &TransformCacheQueueEntry::mLink> mTransformQueue;
  InList<BroadphaseQueueEntry, &BroadphaseQueueEntry::mLink> mBroadphaseQueue;
  InList<MassComputationQueueEntry, &MassComputationQueueEntry::mLink> mMassQueue;
  HierarchyBuildingTask mHierarchyBuildingTask;
};

}//namespace Physics2dTCS
