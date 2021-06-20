#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2dCore
{

class Constraint2dVelocity;
class Constraint2dMass;
class Constraint2dMolecule;
class Jacobian2d;
class Body2dInfo;

//-------------------------------------------------------------------Constraint2dFragments
class Constraint2dFragments
{
public:
  static void Load(const RigidBody2d* body0, const RigidBody2d* body1, Constraint2dVelocity& velocity, Constraint2dMass& mass);
  static void Load(const Body2dInfo& body0Info, const Body2dInfo& body1Info, Constraint2dVelocity& velocity, Constraint2dMass& mass);
  static float ComputeEffectiveMass(const Jacobian2d& jacobian, const Constraint2dMass& mass);
  static float ComputeLambda(const Constraint2dVelocity& velocity, const Constraint2dMass& mass, const Constraint2dMolecule& molecule);
  static void ApplyImpulse(Constraint2dVelocity& velocity, const Constraint2dMass& mass, const Jacobian2d& jacobian, float impulse);
};

}//namespace Physics2dCore
