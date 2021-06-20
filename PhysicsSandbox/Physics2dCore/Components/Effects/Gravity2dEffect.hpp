#pragma once

#include "Physics2dCoreStandard.hpp"

#include "Physics2dCore/Components/Effects/Physics2dEffect.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Gravity2dEffect
class Gravity2dEffect : public Physics2dEffect
{
public:
  ZilchDeclareType(Gravity2dEffect, TypeCopyMode::ReferenceType);
  Gravity2dEffect();

  float GetStrength() const;
  void SetStrength(float strength);

  const Vector2& GetDirection() const;
  void SetDirection(const Vector2& direction);

  Vector2 GetGravity() const;
  Vector2 GetGravityForce(float invMass) const;

protected:
  float mStrength = 9.81f;
  Vector2 mDirection = -Vector2::cYAxis;
};

}//namespace Physics2dCore
