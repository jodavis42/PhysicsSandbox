#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Constraint2dAtom
class Constraint2dAtom
{
public:
  float mTotalImpulse = 0.0f;
  union
  {
    float mError = 0.0f;
    float mValue;
  };
};

}//namespace Physics2dCore
