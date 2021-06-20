#include "Precompiled.hpp"

#include "Gravity2dEffect.hpp"

namespace Physics2dCore
{

using namespace Zero;

//-------------------------------------------------------------------Gravity2dEffect
ZilchDefineType(Gravity2dEffect, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();

  ZilchBindGetterSetterProperty(Strength)->ZeroSerialize(9.81f);
  ZilchBindGetterSetterProperty(Direction)->ZeroSerialize(-Vector2::cYAxis);
}

Gravity2dEffect::Gravity2dEffect()
{
  mEffectType = Physics2dEffectType::Gravity;
}

float Gravity2dEffect::GetStrength() const
{
  return mStrength;
}

void Gravity2dEffect::SetStrength(float strength)
{
  mStrength = strength;
}

const Vector2& Gravity2dEffect::GetDirection() const
{
  return mDirection;
}

void Gravity2dEffect::SetDirection(const Vector2& direction)
{
  mDirection = direction;
}

Vector2 Gravity2dEffect::GetGravity() const
{
  if(!GetActive())
    return Vector2::cZero;

  return GetDirection() * GetStrength();
}

Vector2 Gravity2dEffect::GetGravityForce(float invMass) const
{
  Vector2 gravityAcceleration = GetGravity();
  if(invMass != 0.0f)
    return gravityAcceleration / invMass;
  return Vector2::cZero;
}

}//namespace Physics2dCore
