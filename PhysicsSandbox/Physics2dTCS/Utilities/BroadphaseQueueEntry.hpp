#pragma once

#include "Physics2dStandardTCS.hpp"

#include "SandboxSpatialPartitions/Broadphase2d/CoreStructs.hpp"

namespace Physics2dTCS
{

//-------------------------------------------------------------------BroadphaseQueueEntry
/// Queue element for keeping track of pending broadphase updates needed for a collider.
class BroadphaseQueueEntry
{
public:
  using MaskType = unsigned char;
  void Initialize(Collider2dTCS* collider);

  void QueueInsert(BroadphaseLayerType::Enum layerType);
  void QueueUpdate(BroadphaseLayerType::Enum layerType);
  void QueueRemove(BroadphaseLayerType::Enum layerType);
  
  void Update(float dt, IBroadphase2dManager* broadphase);

  bool mQueued = false;
  MaskType mInsert;
  MaskType mUpdate;
  MaskType mRemove;

  BroadphaseLayerType::Enum mCurrentLayer = (BroadphaseLayerType::Enum)-1;
  Collider2dTCS* mCollider = nullptr;

  SandboxBroadphase2d::BroadphaseKey mKey;
  Link<BroadphaseQueueEntry> mLink;
};

}//namespace Physics2dTCS
