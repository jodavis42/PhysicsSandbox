#pragma once

#include "Physics2dStandardTCS.hpp"

#include "Components/Collider2dTCS.hpp"
#include "Components/RigidBody2dTCS.hpp"
#include "Physics2dTCS/Utilities/Physics2dQueues.hpp"

namespace Physics2dCore
{
class ComponentCreatedEvent;
}//namespace Physics2dCore

namespace Physics2dTCS
{

//-------------------------------------------------------------------PhysicsSpace2dTCS
class PhysicsSpace2dTCS : public Zero::Component
{
public:
  ZilchDeclareType(PhysicsSpace2dTCS, TypeCopyMode::ReferenceType);

  void Initialize(Zero::CogInitializer& initializer);
  void OnSystemLogicUpdate(Zero::UpdateEvent* updateEvent);

  void IterateTimestep(float dt);
  void UpdateQueues(float dt);
  void IntegrateBodiesVelocity(float dt);
  void IntegrateBodiesPosition(float dt);
  void Publish();

  void OnCollider2dCreated(Physics2dCore::ComponentCreatedEvent* e);
  void OnRigidBody2dCreated(Physics2dCore::ComponentCreatedEvent* e);

  void Add(RigidBody2dTCS* rigidBody);
  void Remove(RigidBody2dTCS* rigidBody);
  void Add(Collider2dTCS* collider);
  void Remove(Collider2dTCS* collider);
  void QueueMassUpdate(RigidBody2dTCS* rigidBody);
  void QueueBroadphaseUpdate(Collider2dTCS* collider);

  BaseInList<RigidBody2dTCS, RigidBody2dTCS, &RigidBody2dTCS::mSpaceLink> mRigidBodies;
  BaseInList<Collider2dTCS, Collider2dTCS, &Collider2dTCS::mSpaceLink> mColliders;
  Physics2dQueues mQueues;
};

}//namespace Physics2d
