#include "Precompiled.hpp"

#include "Drag2dEffect.hpp"

namespace Physics2dCore
{

using namespace Zero;

//-------------------------------------------------------------------Drag2dEffect
ZilchDefineType(Drag2dEffect, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();

  ZilchBindGetterSetterProperty(LinearDamping)->ZeroSerialize(0.2f);
  ZilchBindGetterSetterProperty(AngularDamping)->ZeroSerialize(0.1f);
  ZilchBindGetterSetterProperty(LinearDrag)->ZeroSerialize(0);
  ZilchBindGetterSetterProperty(AngularDrag)->ZeroSerialize(0);
}

Drag2dEffect::Drag2dEffect()
{
  mEffectType = Physics2dEffectType::Drag;
}

float Drag2dEffect::GetLinearDamping() const
{
  return mLinearDamping;
}

void Drag2dEffect::SetLinearDamping(float linearDamping)
{
  mLinearDamping = linearDamping;
}

float Drag2dEffect::GetAngularDamping() const
{
  return mAngularDamping;
}

void Drag2dEffect::SetAngularDamping(float angularDamping)
{
  mAngularDamping = angularDamping;
}

float Drag2dEffect::GetLinearDrag() const
{
  return mLinearDrag;
}

void Drag2dEffect::SetLinearDrag(float linearDrag)
{
  mLinearDrag = linearDrag;
}

float Drag2dEffect::GetAngularDrag() const
{
  return mAngularDrag;
}

void Drag2dEffect::SetAngularDrag(float angularDrag)
{
  mAngularDrag = angularDrag;
}

Vector2 Drag2dEffect::ComputeForce(float dt, const Vector2& linearVelocity, float invMass) const
{
  if(!GetActive())
    return Vector2::cZero;

  // Deal with dt being 0 (timescale of 0 for instance)
  float invDt = 0;
  if(dt != 0)
    invDt = 1 / dt;

  // Clamp the max linear damping values so that they can't reverse
  // the object's direction (and explode) but will instead exactly stop the object.
  float linearDamping = Math::Min(mLinearDamping, invDt);

  Vector2 force = -linearVelocity * mLinearDrag;
  if(linearDamping != 0.0f && invMass != 0.0f)
  {
    Vector2 linearAcceleration = -linearVelocity * linearDamping;
    force += invMass * linearAcceleration;
  }
  return force;
}

float Drag2dEffect::ComputeTorque(float dt, float angularVelocity, float invInertia) const
{
  if(!GetActive())
    return 0.0f;

  // Deal with dt being 0 (timescale of 0 for instance)
  float invDt = 0;
  if(dt != 0)
    invDt = 1 / dt;

  // Clamp the max angular damping values so that they can't reverse
  // the object's direction (and explode) but will instead exactly stop the object.
  float angularDamping = Math::Min(mAngularDamping, invDt);

  float torque = -angularVelocity * mAngularDrag;
  if(angularDamping != 0.0f && invInertia != 0.0f)
  {
    float angularAcceleration = -angularVelocity * angularDamping;
    torque = invInertia * angularAcceleration;
  }
  return torque;
}

}//namespace Physics2dCore
