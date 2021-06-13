#include "Precompiled.hpp"

#include "ContactManifold2d.hpp"

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
