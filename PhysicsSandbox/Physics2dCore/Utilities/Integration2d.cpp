#include "Precompiled.hpp"

#include "Integration2d.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Integration2d
void Integration2d::IntegrateVelocityEuler(float dt, float invMass, float invInertia, const Vector2& force, float torque, Vector2& linearVelocity, float& angularVelocity)
{
  linearVelocity += dt * invMass * force;
  angularVelocity += dt * invInertia * torque;
}

void Integration2d::IntegratePositionEuler(float dt, const Vector2& linearVelocity, float angularVelocity, Vector2& position, float& rotation)
{
  position += dt * linearVelocity;
  rotation += dt * angularVelocity;
}

}//namespace Physics2dCore
