#include "Precompiled.hpp"

#include "Constraint2dFragments.hpp"

#include "Physics2dCore/Resolution/ConstraintMolecules/Constraint2dMolecule.hpp"
#include "Physics2dCore/Resolution/ConstraintUtilities/Body2dInfo.hpp"
#include "Physics2dCore/Resolution/ConstraintUtilities/Constraint2dMath.hpp"
#include "Physics2dCore/Resolution/ConstraintUtilities/Constraint2dMass.hpp"
#include "Physics2dCore/Resolution/ConstraintUtilities/Constraint2dVelocity.hpp"
#include "Physics2dCore/Resolution/ConstraintUtilities/Jacobian2d.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Constraint2dFragments
void Constraint2dFragments::Load(const RigidBody2d* body0, const RigidBody2d* body1, Constraint2dVelocity& velocity, Constraint2dMass& mass)
{
  Body2dInfo body0Info, body1Info;
  body0Info.Load(body0);
  body1Info.Load(body1);

  Load(body0Info, body1Info, velocity, mass);
}

void Constraint2dFragments::Load(const Body2dInfo& body0Info, const Body2dInfo& body1Info, Constraint2dVelocity& velocity, Constraint2dMass& mass)
{
  velocity.Set(body0Info.mLinearVelocity, body0Info.mAngularVelocity, body1Info.mLinearVelocity, body1Info.mAngularVelocity);
  mass.Set(body0Info.mInvMass, body0Info.mInvInertia, body1Info.mInvMass, body1Info.mInvInertia);
}

float Constraint2dFragments::ComputeEffectiveMass(const Jacobian2d& jacobian, const Constraint2dMass& mass)
{
  float effectiveMass = 0;
  effectiveMass += Math::Dot(jacobian.Linear0(), jacobian.Linear0()) * mass.InvMass0();
  effectiveMass += Math::Dot(jacobian.Linear1(), jacobian.Linear1()) * mass.InvMass1();
  effectiveMass += jacobian.Angular0() * jacobian.Angular0() * mass.InvInertia0();
  effectiveMass += jacobian.Angular1() * jacobian.Angular1() * mass.InvInertia1();
  return effectiveMass;
}

float Constraint2dFragments::ComputeLambda(const Constraint2dVelocity& velocity, const Constraint2dMass& mass, const Constraint2dMolecule& molecule)
{
  auto&& jacobian = molecule.mJacobian;
  float effectiveMass = ComputeEffectiveMass(jacobian, mass);
  float jv = Constraint2dMath::Dot(jacobian, velocity);

  float bias = molecule.mBias - molecule.mError;
  float impulse = -(jv + bias);
  impulse /= effectiveMass;

  float totalImpulse = Math::Clamp(impulse + molecule.mTotalImpulse, molecule.mMinImpulse, molecule.mMaxImpulse);
  float deltaImpulse = totalImpulse - molecule.mTotalImpulse;

  return deltaImpulse;
}

void Constraint2dFragments::ApplyImpulse(Constraint2dVelocity& velocity, const Constraint2dMass& mass, const Jacobian2d& jacobian, float impulse)
{
  Constraint2dVector impulseVector;

  impulseVector.Linear0() = impulse * mass.InvMass0() * jacobian.Linear0();
  impulseVector.Angular0() = impulse * mass.InvInertia0() * jacobian.Angular0();
  impulseVector.Linear1() = impulse * mass.InvMass1() * jacobian.Linear1();
  impulseVector.Angular1() = impulse * mass.InvInertia1() * jacobian.Angular1();

  velocity += impulseVector;
}

}//namespace Physics2dCore
