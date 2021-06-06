#include "Precompiled.hpp"

#include "RigidBody2dTCS.hpp"

#include "Physics2dCore/Components/RigidBody2d.hpp"
#include "Physics2dCore/Events/PropertyChangedEvent.hpp"

#include "Physics2dTCS/Components/PhysicsSpace2dTCS.hpp"

using namespace Zero;

namespace Physics2dTCS
{

//-------------------------------------------------------------------RigidBody2dTCS
ZilchDefineType(RigidBody2dTCS, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();
  ZeroBindDependency(Zero::Cog);

  type->IsHidden = true;
  type->AddAttribute(ObjectAttributes::cHidden);
}

void RigidBody2dTCS::Initialize(Zero::CogInitializer& initializer)
{
  mRigidBody2d = GetOwner()->has(RigidBody2d);
  mPhysicsSpace2d = GetSpace()->has(PhysicsSpace2dTCS);
  mPhysicsSpace2d->Add(this);
  mMassQueueEntry.Initialize(this);

  ConnectThisTo(GetOwner(), Physics2dCore::Events::RigidBody2dPropertyChanged, OnRigidBody2dPropertyChanged);
}

void RigidBody2dTCS::RigidBody2dTCS::ComponentRemoved(BoundType* typeId, Component* component)
{
  if(typeId == ZilchTypeId(RigidBody2d))
  {
    mRigidBody2d = nullptr;
    mPhysicsSpace2d->Remove(this);
  }
}

void RigidBody2dTCS::UpdateAfterIntegrationInternal(const Vector2& worldCenterOfMass, float worldRotation)
{
  mRigidBody2d->SetWorldRotationNoEvent(worldRotation);
  mRigidBody2d->SetWorldCenterOfMassNoEvent(worldCenterOfMass);
}

void RigidBody2dTCS::OnRigidBody2dPropertyChanged(PropertyChangedEvent* e)
{
  if(e->mFlags.IsSet(Physics2dCore::PropertyChangedFlags::RecomputeMassProperties))
    QueueMassUpdate();
}

void RigidBody2dTCS::QueueMassUpdate()
{
  mPhysicsSpace2d->QueueMassUpdate(this);
}

}//namespace Physics2dTCS
