#include "Precompiled.hpp"

#include "Contact2dMolecules.hpp"

#include "Physics2dCore/Components/Colliders/Collider2d.hpp"

#include "Physics2dCore/Resolution/ConstraintMolecules/Constraint2dMolecule.hpp"
#include "Physics2dCore/Resolution/ConstraintMolecules/Constraint2dMoleculeWalker.hpp"
#include "Physics2dCore/Resolution/ConstraintUtilities/Body2dInfo.hpp"
#include "Physics2dCore/Resolution/ConstraintUtilities/Constraint2dFragments.hpp"
#include "Physics2dCore/Resolution/ConstraintUtilities/Constraint2dMath.hpp"
#include "Physics2dCore/Resolution/ConstraintUtilities/Constraint2dMass.hpp"
#include "Physics2dCore/Resolution/ConstraintUtilities/Constraint2dVelocity.hpp"
#include "Physics2dCore/Resolution/ConstraintUtilities/Jacobian2d.hpp"
#include "Physics2dCore/Resolution/ConstraintUtilities/ContactConstraint2dManifold.hpp"

#include "Physics2dCore/Resources/Physics2dMaterial.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Contact2dMolecules
size_t Contact2dMolecules::Size(const ContactConstraint2dManifold& manifold)
{
  return manifold.Size() * 2;
}

void Contact2dMolecules::ComputeMolecules(const ContactConstraint2dManifold& manifold, Constraint2dMoleculeWalker& molecules)
{
  Body2dInfo body0Info, body1Info;
  body0Info.Load(manifold.mColliders[0]);
  body1Info.Load(manifold.mColliders[1]);

  Constraint2dVelocity velocities;
  Constraint2dMass masses;
  Constraint2dFragments::Load(body0Info, body1Info, velocities, masses);

  float restitution, friction;
  ComputeSurfaceInfo(manifold, restitution, friction);
  float baumgarte = 2.0f;
  float slop = 0.01f;
  float velocityRestitutionThreshold = 1;

  for(size_t i = 0; i < manifold.Size(); ++i)
  {
    auto&& contactPoint = manifold[i];

    Vector2 normal = contactPoint.mNormal;
    Vector2 tangent = Vector2(normal.y, -normal.x);
    Vector2 r0 = contactPoint.mPoints[0] - body0Info.mCenterOfMass;
    Vector2 r1 = contactPoint.mPoints[1] - body1Info.mCenterOfMass;

    // Setup the normal impulse constraint
    auto&& normalMolecule = *molecules;
    normalMolecule.mTotalImpulse = contactPoint.mAccumulatedImpulse[0];
    normalMolecule.mJacobian.Set(-normal, -Math::Cross(r0, normal), normal, Math::Cross(r1, normal));
    normalMolecule.mMinImpulse = 0;
    normalMolecule.mMaxImpulse = Math::PositiveMax();

    // Compute bias/error
    float relativeVelocity = Constraint2dMath::Dot(normalMolecule.mJacobian, velocities);
    // Don't apply restitution if the relative velocity is too small (prevent micro bounces)
    if(Math::Abs(relativeVelocity) < velocityRestitutionThreshold)
      restitution = 0;
    normalMolecule.mBias = restitution * relativeVelocity;
    normalMolecule.mError = Math::Max(0.0f, contactPoint.mPenetrationDistance - slop) * baumgarte;
    ++molecules;

    // Setup the tangent impulse constraint
    auto&& tangentMolecule = *molecules;
    tangentMolecule.mTotalImpulse = contactPoint.mAccumulatedImpulse[1];
    tangentMolecule.mJacobian.Set(-tangent, -Math::Cross(r0, tangent), tangent, Math::Cross(r1, tangent));
    float frictionLimit = contactPoint.mAccumulatedImpulse[0] * friction;
    tangentMolecule.mMinImpulse = -frictionLimit;
    tangentMolecule.mMaxImpulse = frictionLimit;
    ++molecules;
  }
}

void Contact2dMolecules::ComputeSurfaceInfo(const ContactConstraint2dManifold& manifold, float& restitution, float& friction)
{
  auto&& material0 = *manifold.GetCollider(0)->GetMaterial();
  auto&& material1 = *manifold.GetCollider(1)->GetMaterial();
  friction = ComputeFriction(material0, material1);
  restitution = ComputeRestitution(material0, material1);
}

float Contact2dMolecules::ComputeFriction(const Physics2dMaterial& material0, const Physics2dMaterial& material1)
{
  float friction = 0;
  if(material0.mFrictionImportance > material1.mFrictionImportance)
    friction = material0.mStaticFriction;
  else if(material0.mFrictionImportance > material1.mFrictionImportance)
    friction = material1.mStaticFriction;
  else
    friction = Math::Sqrt(material0.mStaticFriction * material1.mStaticFriction);
  return friction;
}

float Contact2dMolecules::ComputeRestitution(const Physics2dMaterial& material0, const Physics2dMaterial& material1)
{
  float restitution;
  if(material0.mRestitutionImportance > material1.mRestitutionImportance)
    restitution = material0.mRestitution;
  else if(material0.mRestitutionImportance > material1.mRestitutionImportance)
    restitution = material1.mRestitution;
  else
    restitution = Math::Max(material0.mRestitution, material1.mRestitution);
  return restitution;
}

}//namespace Physics2dCore
