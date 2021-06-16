#pragma once

#include "Physics2dStandardTCS.hpp"
#include "Physics2dCore/Utilities/MassProperties2d.hpp"
#include "Physics2dTCS/Utilities/BroadphaseQueueEntry.hpp"

namespace Physics2dCore
{
class ComponentCreatedEvent;
}

namespace Physics2dTCS
{

//-------------------------------------------------------------------Collider2dTCS
class Collider2dTCS : public Zero::Component
{
public:
  ZilchDeclareType(Collider2dTCS, TypeCopyMode::ReferenceType);

  void Initialize(Zero::CogInitializer& initializer);

  Physics2dCore::ColliderMassProperties2d GetMassProperties() const;
  void TransformUpdate(Zero::TransformUpdateInfo& info) override;
  void ComponentRemoved(BoundType* typeId, Component* component) override;

  void OnCollider2dPropertyChanged(PropertyChangedEvent* e);

  BroadphaseLayerType::Enum GetLayerType();
  void QueueBroadphaseInsert();
  void QueueBroadphaseUpdate();
  void QueueBroadphaseRemove();
  
  Collider2d* mCollider2d = nullptr;
  RigidBody2dTCS* mActiveBody = nullptr;
  PhysicsSpace2dTCS* mPhysicsSpace2d = nullptr;

  Zero::Link<Collider2dTCS> mBodyLink;
  Zero::Link<Collider2dTCS> mSpaceLink;
  BroadphaseQueueEntry mBroadphaseQueueEntry;
};

}//namespace Physics2dTCS
