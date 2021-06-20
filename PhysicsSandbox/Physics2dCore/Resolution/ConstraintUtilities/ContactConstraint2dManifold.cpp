#include "Precompiled.hpp"

#include "ContactConstraint2dManifold.hpp"

#include "Physics2dCore/Components/Colliders/Collider2d.hpp"
#include "Physics2dCore/Components/RigidBody2d.hpp"
#include "Physics2dCore/Detection/ContactManifold2d.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------ContactConstraint2dManifold
const Collider2d* ContactConstraint2dManifold::GetCollider(size_t index)
{
  return mColliders[index];
}

const Collider2d* ContactConstraint2dManifold::GetCollider(size_t index) const
{
  return mColliders[index];
}

RigidBody2d* ContactConstraint2dManifold::GetRigidBody(size_t index) const
{
  return mColliders[index]->GetOwner()->has(RigidBody2d);
}

size_t ContactConstraint2dManifold::Size() const
{
  return mContactPoints.Size();
}

ContactConstraint2dPoint& ContactConstraint2dManifold::operator[](size_t index)
{
  return mContactPoints[index];
}

const ContactConstraint2dPoint& ContactConstraint2dManifold::operator[](size_t index) const
{
  return mContactPoints[index];
}

void ContactConstraint2dManifold::Load(const ContactManifold2d& contactManifold)
{
  size_t pointCount = contactManifold.TotalPointCount();
  mContactPoints.Clear();
  mContactPoints.Reserve(pointCount);
  for(size_t featureIndex = 0; featureIndex < contactManifold.ContactSubFeatureContactCount(); ++featureIndex)
  {
    auto&& feature = contactManifold.GetSubFeatureContact(featureIndex);
    for(size_t pointIndex = 0; pointIndex < feature.mPointCount; ++pointIndex)
    {
      auto&& point = feature.mPoints[pointIndex];
      auto&& cachedPoint = mContactPoints.PushBack();
      cachedPoint.mNormal = point.mNormal;
      cachedPoint.mPenetrationDistance = point.mPenetrationDistance;
      cachedPoint.mPoints[0] = point.mPoints[0];
      cachedPoint.mPoints[1] = point.mPoints[1];
      cachedPoint.mFeatureId = feature.mFeatureId;
    }
  }
  mColliders = contactManifold.mColliders;
}

}//namespace Physics2dCore
