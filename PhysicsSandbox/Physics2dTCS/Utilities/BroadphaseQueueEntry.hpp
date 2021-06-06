#pragma once

#include "Physics2dStandardTCS.hpp"

namespace Physics2dTCS
{

//-------------------------------------------------------------------BroadphaseQueueEntry
/// Queue element for keeping track of pending broadphase updates needed for a collider.
class BroadphaseQueueEntry
{
public:
  void Initialize(Collider2dTCS* collider);
  void Update(float dt);

  bool mQueued = false;
  bool mInsert = false;
  bool mUpdate = false;
  bool mRemove = false;
  Collider2dTCS* mCollider = nullptr;

  Link<BroadphaseQueueEntry> mLink;
};

}//namespace Physics2dTCS
