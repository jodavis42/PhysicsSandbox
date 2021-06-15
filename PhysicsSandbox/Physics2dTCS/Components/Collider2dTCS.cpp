#include "Precompiled.hpp"

#include "Collider2dTCS.hpp"

#include "Physics2dCore/Components/Colliders/Collider2d.hpp"

#include "Physics2dCore/Components/Colliders/BoxCollider2d.hpp"
#include "Physics2dCore/Components/Colliders/CircleCollider2d.hpp"
#include "Physics2dCore/Events/PropertyChangedEvent.hpp"

#include "Physics2dTCS/Components/PhysicsSpace2dTCS.hpp"
#include "Physics2dCore/Utilities/Collider2dShapes.hpp"

using namespace Zero;

namespace Physics2dTCS
{

//-------------------------------------------------------------------Collider2dTCS
ZilchDefineType(Collider2dTCS, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();
  ZeroBindDependency(Zero::Cog);

  type->IsHidden = true;
  type->AddAttribute(ObjectAttributes::cHidden);
}

void Collider2dTCS::Initialize(Zero::CogInitializer& initializer)
{
  mCollider2d = GetOwner()->has(Collider2d);
  mPhysicsSpace2d = GetSpace()->has(PhysicsSpace2dTCS);
  mPhysicsSpace2d->Add(this);
  mBroadphaseQueueEntry.Initialize(this);

  ConnectThisTo(GetOwner(), Physics2dCore::Events::Collider2dPropertyChanged, OnCollider2dPropertyChanged);
}

void Collider2dTCS::ComponentRemoved(BoundType* typeId, Component* component)
{
  if(typeId == ZilchTypeId(Collider2d))
  {
    mPhysicsSpace2d->Remove(this);
  }
}

Physics2dCore::ColliderMassProperties2d Collider2dTCS::GetMassProperties() const
{
  Physics2dCore::ColliderMassProperties2d results = mCollider2d->ComputeMassProperties();
  results.mDensity = mCollider2d->GetDensity();
  return results;
}

void Collider2dTCS::OnCollider2dPropertyChanged(PropertyChangedEvent* e)
{
  if(e->mFlags.IsSet(Physics2dCore::PropertyChangedFlags::RecomputeMassProperties) && mActiveBody != nullptr)
    mActiveBody->QueueMassUpdate();
  if(e->mFlags.IsSet(Physics2dCore::PropertyChangedFlags::UpdateSpatialPartition))
    QueueBroadphaseUpdate();
}

void Collider2dTCS::QueueBroadphaseUpdate()
{
  mPhysicsSpace2d->QueueBroadphaseUpdate(this);
}

}//namespace Physics2dTCS
