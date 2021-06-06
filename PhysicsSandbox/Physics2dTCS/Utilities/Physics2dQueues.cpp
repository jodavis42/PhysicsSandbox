#include "Precompiled.hpp"

#include "Physics2dQueues.hpp"

namespace Physics2dTCS
{

//-------------------------------------------------------------------Physics2dQueues
void Physics2dQueues::Queue(MassComputationQueueEntry& entry)
{
  if(entry.mQueued == true)
    return;
  entry.mQueued = true;
  mMassQueue.PushBack(&entry);
}

void Physics2dQueues::Queue(BroadphaseQueueEntry& entry)
{
  if(entry.mQueued == true)
    return;
  entry.mQueued = true;
  mBroadphaseQueue.PushBack(&entry);
}

void Physics2dQueues::Queue(TransformCacheQueueEntry& entry)
{
  if(entry.mQueued == true)
    return;
  entry.mQueued = true;
  mTransformQueue.PushBack(&entry);
}

void Physics2dQueues::Update(float dt)
{
  mHierarchyBuildingTask.Update();
  UpdateMasses(dt);
  UpdateBroadphase(dt);
  UpdateTransformCache(dt);
}

void Physics2dQueues::UpdateMasses(float dt)
{
  for(auto&& range = mMassQueue.All(); !range.Empty(); range.PopFront())
  {
    auto&& entry = range.Front();
    entry.Update(dt);
    entry.mQueued = false;
  }
  mMassQueue.Clear();
}

void Physics2dQueues::UpdateBroadphase(float dt)
{
  for(auto&& range = mBroadphaseQueue.All(); !range.Empty(); range.PopFront())
  {
    auto&& entry = range.Front();
    entry.Update(dt);
    entry.mQueued = false;
  }
  mBroadphaseQueue.Clear();
}

void Physics2dQueues::UpdateTransformCache(float dt)
{
  for(auto&& range = mTransformQueue.All(); !range.Empty(); range.PopFront())
  {
    auto&& entry = range.Front();
    entry.mQueued = false;
  }
  mTransformQueue.Clear();
}

}//namespace Physics2dTCS