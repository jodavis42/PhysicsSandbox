#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

#include "Physics2dCore/Resolution/ConstraintUtilities/Jacobian2d.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Constraint2dMolecule
class Constraint2dMolecule
{
public:
  Constraint2dMolecule()
  {
    mMinImpulse = -Math::PositiveMax();
    mMaxImpulse = Math::PositiveMax();
  }
  Jacobian2d mJacobian;
  float mMinImpulse = -Math::PositiveMax();
  float mMaxImpulse = Math::PositiveMax();
  float mBias = 0.0f;
  float mError = 0.0f;
  float mTotalImpulse = 0.0f;
};

}//namespace Physics2dCore
