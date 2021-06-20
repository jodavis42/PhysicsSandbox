#pragma once

#include "Physics2dCoreStandard.hpp"

#include "Physics2dCore/Components/Effects/Physics2dEffect.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Drag2dEffect
class Drag2dEffect : public Physics2dEffect
{
public:
  ZilchDeclareType(Drag2dEffect, TypeCopyMode::ReferenceType);
  Drag2dEffect();

  float GetLinearDamping() const;
  void SetLinearDamping(float linearDamping);

  float GetAngularDamping() const;
  void SetAngularDamping(float angularDamping);

  float GetLinearDrag() const;
  void SetLinearDrag(float linearDrag);

  float GetAngularDrag() const;
  void SetAngularDrag(float angularDrag);

  Vector2 ComputeForce(float dt, const Vector2& linearVelocity, float invMass) const;
  float ComputeTorque(float dt, float angularVelocity, float invInertia) const;

protected:

  float mLinearDamping = 0.2f;
  float mAngularDamping = 0.1f;
  float mLinearDrag = 0;
  float mAngularDrag = 0;
};

}//namespace Physics2dCore
