#include "Precompiled.hpp"

#include "Physics2dEffectTCS.hpp"

#include "Physics2dCore/Components/RigidBody2d.hpp"
#include "Physics2dCore/Components/Effects/Physics2dEffect.hpp"
#include "Physics2dCore/Components/Effects/Gravity2dEffect.hpp"
#include "Physics2dCore/Components/Effects/Drag2dEffect.hpp"

using namespace Zero;

namespace Physics2dTCS
{

//-------------------------------------------------------------------Physics2dEffectTCS
void Physics2dEffectTCS::ComputeForces(Physics2dCore::Physics2dEffect& effect, float dt, Physics2dCore::RigidBody2d& body)
{
  float invMass = body.GetInvMass();
  float invInertia = body.GetInvInertia();
  Vector2 linearVelocity = body.GetLinearVelocity();
  float angularVelocity = body.GetAngularVelocity();
  Vector2 force = body.GetForce();
  float torque = body.GetTorque();
  ComputeForces(effect, dt, linearVelocity, invMass, force, angularVelocity, invInertia, torque);
}

void Physics2dEffectTCS::ComputeForces(Physics2dCore::Physics2dEffect& effect, float dt,
  const Vector2& linearVelocity, float invMass, Vector2& force,
  float angularVelocity, float invInertia, float& torque)
{
  if(effect.GetActive() == false)
    return;

  if(effect.GetEffectType() == Physics2dCore::Physics2dEffectType::Drag)
  {
    const Physics2dCore::Drag2dEffect& dragEffect = static_cast<const Physics2dCore::Drag2dEffect&>(effect);
    force += dragEffect.ComputeForce(dt, linearVelocity, invMass);
    torque += dragEffect.ComputeTorque(dt, angularVelocity, invInertia);
  }
  else if(effect.GetEffectType() == Physics2dCore::Physics2dEffectType::Gravity)
  {
    const Physics2dCore::Gravity2dEffect& gravityEffect = static_cast<const Physics2dCore::Gravity2dEffect&>(effect);
    force += gravityEffect.GetGravityForce(invMass);
  }
}

}//namespace Physics2dTCS
