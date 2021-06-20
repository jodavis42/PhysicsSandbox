#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

#include "SandboxGeometry/Intersection2d/ManifoldPoint2d.hpp"
#include "Physics2dCore/Utilities/Collider2dPair.hpp"

namespace Physics2dCore
{

class ContactManifold2d;

//-------------------------------------------------------------------ContactConstraint2dPoint
class ContactConstraint2dPoint : public SandboxGeometry::ManifoldPoint2d
{
public:
  size_t mFeatureId = -1;
  Vector2 mAccumulatedImpulse = Vector2::cZero;
};

//-------------------------------------------------------------------ContactConstraint2dManifold
class ContactConstraint2dManifold
{
public:
  const Collider2d* GetCollider(size_t index);
  const Collider2d* GetCollider(size_t index) const;
  RigidBody2d* GetRigidBody(size_t index) const;

  size_t Size() const;
  ContactConstraint2dPoint& operator[](size_t index);
  const ContactConstraint2dPoint& operator[](size_t index) const;

  void Load(const ContactManifold2d& contactManifold);

  Zero::Array<ContactConstraint2dPoint> mContactPoints;
  Collider2dPair mColliders;
};

}//namespace Physics2dCore
