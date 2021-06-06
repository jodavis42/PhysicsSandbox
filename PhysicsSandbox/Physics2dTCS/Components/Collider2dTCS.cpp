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
  Physics2dCore::ColliderMassProperties2d results;
  results.mDensity = mCollider2d->GetDensity();
  auto&& colliderType = mCollider2d->GetColliderType();
  if(colliderType == Physics2dCore::Collider2dType::Box2d)
  {
    const Physics2dCore::BoxCollider2d* boxCollider = static_cast<const Physics2dCore::BoxCollider2d*>(mCollider2d);
    SandboxGeometry::Obb2d obb2d = Physics2dCore::Collider2dShapes::GetShape(*boxCollider);
    results.mArea = obb2d.mHalfExtents[0] * obb2d.mHalfExtents[1] * 4;
    results.mCenterOfMass = obb2d.mCenter;
  }
  else if(colliderType == Physics2dCore::Collider2dType::Box2d)
  {
    const Physics2dCore::CircleCollider2d* circleCollider = static_cast<const Physics2dCore::CircleCollider2d*>(mCollider2d);
    SandboxGeometry::Circle2d circle2d = Physics2dCore::Collider2dShapes::GetShape(*circleCollider);
    results.mArea = 2 * Math::cPi * circle2d.mRadius;
    results.mCenterOfMass = circle2d.mCenter;
  }
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
