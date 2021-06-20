#pragma once

#include "Physics2dStandardTCS.hpp"

namespace Physics2dTCS
{

//-------------------------------------------------------------------Physics2dEffectTCS
class Physics2dEffectTCS
{
public:
  static void ComputeForces(Physics2dCore::Physics2dEffect& effect, float dt, Physics2dCore::RigidBody2d& body);
  static void ComputeForces(Physics2dCore::Physics2dEffect& effect, float dt,
    const Vector2& linearVelocity, float invMass, Vector2& force,
    float angularVelocity, float invInertia, float& torque);
};

}//namespace Physics2dTCS
