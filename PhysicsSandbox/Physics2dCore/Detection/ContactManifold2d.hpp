#pragma once

#include "Physics2dCoreStandard.hpp"

#include "SandboxGeometry/Intersection2d/Manifold2d.hpp"
#include "Physics2dCore/Utilities/Collider2dPair.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------SubFeatureContactManifold2d
class SubFeatureContactManifold2d : public SandboxGeometry::Manifold2d
{
  size_t mFeatureId = -1;
};

//-------------------------------------------------------------------ContactManifold2d
class ContactManifold2d
{
public:
  const Collider2d* GetCollider(size_t index);
  const Collider2d* GetCollider(size_t index) const;
  RigidBody2d* GetRigidBody(size_t index);
  const RigidBody2d* GetRigidBody(size_t index) const;

  void AddSubFeatureContact(const SubFeatureContactManifold2d& subFeatureContact);
  size_t ContactSubFeatureContactCount() const;
  SubFeatureContactManifold2d& GetSubFeatureContact(size_t index);
  const SubFeatureContactManifold2d& GetSubFeatureContact(size_t index) const;

  Collider2dPair mColliders;
  Zero::Array<SubFeatureContactManifold2d> mSubFeaturesContacts;
};

}//namespace Physics2dCore
