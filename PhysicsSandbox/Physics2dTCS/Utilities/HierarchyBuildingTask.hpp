#pragma once

#include "Physics2dStandardTCS.hpp"

namespace Physics2dTCS
{

//-------------------------------------------------------------------HierarchyBuildingTask
/// Queue element for keeping track of pending hierarchy connections needing updates for components.
class HierarchyBuildingTask
{
public:
  void BodyAdded(RigidBody2dTCS* body);
  void BodyRemoved(RigidBody2dTCS* body);

  void ColliderAdded(Collider2dTCS* collider);
  void ColliderRemoved(Collider2dTCS* collider);

  void Update();

private:
  RigidBody2dTCS* FindActiveBody(Zero::Cog* cog);

  Array<Collider2dTCS*> mNewColliders;
  Array<Collider2dTCS*> mRemovedColliders;
  Array<RigidBody2dTCS*> mNewBodies;
  Array<RigidBody2dTCS*> mRemovedBodies;
};

}//namespace Physics2dTCS
