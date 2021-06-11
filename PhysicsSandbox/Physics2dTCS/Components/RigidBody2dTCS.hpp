#pragma once

#include "Physics2dStandardTCS.hpp"

#include "Physics2dTCS/Components/Collider2dTCS.hpp"
#include "Physics2dTCS/Utilities/MassComputationQueueEntry.hpp"

namespace Physics2dCore
{
class ComponentCreatedEvent;
}

namespace Physics2dTCS
{

//-------------------------------------------------------------------RigidBody2dTCS
class RigidBody2dTCS : public Zero::Component
{
public:
  ZilchDeclareType(RigidBody2dTCS, TypeCopyMode::ReferenceType);

  void Initialize(Zero::CogInitializer& initializer) override;
  void TransformUpdate(Zero::TransformUpdateInfo& info) override;
  void ComponentRemoved(BoundType* typeId, Component* component) override;

  void UpdateAfterIntegrationInternal(const Vector2& worldCenterOfMass, float worldRotation);
  void OnRigidBody2dPropertyChanged(PropertyChangedEvent* e);

  void QueueMassUpdate();
  
  RigidBody2d* mRigidBody2d = nullptr;
  PhysicsSpace2dTCS* mPhysicsSpace2d = nullptr;

  MassComputationQueueEntry mMassQueueEntry;
  Zero::InList<Collider2dTCS, &Collider2dTCS::mBodyLink> mColliders;
  Zero::Link<RigidBody2dTCS> mSpaceLink;
};

}//namespace Physics2dTCS
