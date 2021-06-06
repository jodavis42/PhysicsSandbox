#include "Precompiled.hpp"

#include "HierarchyBuildingTask.hpp"

#include "Physics2dTCS/Components/Collider2dTCS.hpp"
#include "Physics2dTCS/Components/RigidBody2dTCS.hpp"

namespace Physics2dTCS
{

//-------------------------------------------------------------------HierarchyBuildingTask
void HierarchyBuildingTask::BodyAdded(RigidBody2dTCS* body)
{
  mNewBodies.PushBack(body);
}

void HierarchyBuildingTask::BodyRemoved(RigidBody2dTCS* body)
{
  mRemovedBodies.PushBack(body);
}

void HierarchyBuildingTask::ColliderAdded(Collider2dTCS* collider)
{
  mNewColliders.PushBack(collider);
}

void HierarchyBuildingTask::ColliderRemoved(Collider2dTCS* collider)
{
  mRemovedColliders.PushBack(collider);
}

void HierarchyBuildingTask::Update()
{
  for(auto&& range = mRemovedColliders.All(); !range.Empty(); range.PopFront())
  {
    Collider2dTCS* collider = range.Front();
    if(collider->mActiveBody != nullptr)
      collider->mActiveBody->mColliders.Erase(collider);
    collider->GetOwner()->RemoveComponent(collider);
  }
  mRemovedColliders.Clear();

  for(auto&& range = mNewColliders.All(); !range.Empty(); range.PopFront())
  {
    Collider2dTCS* collider = range.Front();
    collider->mActiveBody = FindActiveBody(collider->GetOwner());
    if(collider->mActiveBody != nullptr)
      collider->mActiveBody->mColliders.PushFront(collider);
  }
  mNewColliders.Clear();

  for(auto&& range = mRemovedBodies.All(); !range.Empty(); range.PopFront())
  {
    RigidBody2dTCS* rigidBody = range.Front();
    rigidBody->GetOwner()->RemoveComponent(rigidBody);
  }
  mRemovedBodies.Clear();
}

RigidBody2dTCS* HierarchyBuildingTask::FindActiveBody(Zero::Cog* cog)
{
  RigidBody2dTCS* activeBody = nullptr;
  while(cog != nullptr)
  {
    activeBody = cog->has(RigidBody2dTCS);
    if(activeBody != nullptr)
      break;
    cog = cog->GetParent();
  }
  return activeBody;

}

}//namespace Physics2dTCS
