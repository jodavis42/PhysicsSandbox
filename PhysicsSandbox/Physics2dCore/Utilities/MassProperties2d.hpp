#pragma once

#include "Physics2dCoreStandard.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------ColliderMassProperties2d
class ColliderMassProperties2d
{
public:
  float mArea = 1.0f;
  float mDensity = 1.0f;
  float mInertia = 1.0f;
  Vector2 mCenterOfMass = Vector2::cZero;
};

//-------------------------------------------------------------------BodyMassProperties2d
class BodyMassProperties2d
{
public:
  float mMass = 1.0f;
  float mInertia = 1.0f;
  Vector2 mCenterOfMass = Vector2::cZero;
};

//-------------------------------------------------------------------MassProperties2d
class MassProperties2d
{
public:
  float mArea = 1.0f;
  float mInertia = 1.0f;
  Vector2 mCenterOfMass = Vector2::cZero;
};

}//namespace Physics2dCore
