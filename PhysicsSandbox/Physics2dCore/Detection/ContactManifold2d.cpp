#include "Precompiled.hpp"

#include "ContactManifold2d.hpp"

#include "Physics2dCore/Components/Colliders/Collider2d.hpp"
#include "Physics2dCore/Components/RigidBody2d.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------ContactManifold2d
const Collider2d* ContactManifold2d::GetCollider(size_t index)
{
  return mColliders[index];
}

const Collider2d* ContactManifold2d::GetCollider(size_t index) const
{
  return mColliders[index];
}

RigidBody2d* ContactManifold2d::GetRigidBody(size_t index)
{
  return mColliders[0]->GetOwner()->has(RigidBody2d);
}

const RigidBody2d* ContactManifold2d::GetRigidBody(size_t index) const
{
  return mColliders[0]->GetOwner()->has(RigidBody2d);
}

void ContactManifold2d::AddSubFeatureContact(const SubFeatureContactManifold2d& subFeatureContact)
{
  mSubFeaturesContacts.PushBack(subFeatureContact);
}

size_t ContactManifold2d::ContactSubFeatureContactCount() const
{
  return mSubFeaturesContacts.Size();
}

SubFeatureContactManifold2d& ContactManifold2d::GetSubFeatureContact(size_t index)
{
  return mSubFeaturesContacts[index];
}

const SubFeatureContactManifold2d& ContactManifold2d::GetSubFeatureContact(size_t index) const
{
  return mSubFeaturesContacts[index];
}

}//namespace Physics2dCore
