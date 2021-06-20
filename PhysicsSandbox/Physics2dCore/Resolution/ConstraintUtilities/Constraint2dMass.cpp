#include "Precompiled.hpp"

#include "Constraint2dMass.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Constraint2dMass
float Constraint2dMass::operator[](size_t index) const
{
  return mData[index];
}

float& Constraint2dMass::operator[](size_t index)
{
  return mData[index];
}

size_t Constraint2dMass::Size() const
{
  return Count;
}

void Constraint2dMass::Set(float invMass0, float invInertia0, float invMass1, float invInertia1)
{
  InvMass0() = invMass0;
  InvInertia0() = invInertia0;
  InvMass1() = invMass1;
  InvInertia1() = invInertia1;
}

float& Constraint2dMass::InvMass0()
{
  return mData[0];
}

const float& Constraint2dMass::InvMass0() const
{
  return mData[0];
}

float& Constraint2dMass::InvInertia0()
{
  return mData[1];
}

const float& Constraint2dMass::InvInertia0() const
{
  return mData[1];
}

float& Constraint2dMass::InvMass1()
{
  return mData[2];
}

const float& Constraint2dMass::InvMass1() const
{
  return mData[2];
}

float& Constraint2dMass::InvInertia1()
{
  return mData[3];
}

const float& Constraint2dMass::InvInertia1() const
{
  return mData[3];
}

}//namespace Physics2dCore
