#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Body2dInfo
class Body2dInfo
{
public:

  void Load(const Collider2d* collider);
  void Load(const RigidBody2d* body);
  void Store(RigidBody2d* body, const Vector2& linearVelocity, float angularVelocity);
  void Reset();

  float mInvMass = 0;
  float mInvInertia = 0;  
  Vector2 mCenterOfMass = Vector2::cZero;
  float mRotation = 0;
  Vector2 mLinearVelocity = Vector2::cZero;
  float mAngularVelocity = 0;
};

}//namespace Physics2dCore
