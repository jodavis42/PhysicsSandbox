#pragma once

#include "Physics2dCoreStandard.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Integration2d
class Integration2d
{
public:
  static void IntegrateVelocityEuler(float dt, float invMass, float invInertia, const Vector2& force, float torque, Vector2& linearVelocity, float& angularVelocity);
  static void IntegratePositionEuler(float dt, const Vector2& linearVelocity, float angularVelocity, Vector2& position, float& rotation);
};

}//namespace Physics2dCore
