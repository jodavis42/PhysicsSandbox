#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2dCore
{

class Jacobian2d;
class Constraint2dVelocity;
class Constraint2dMass;
class Constraint2dVector;

//-------------------------------------------------------------------Constraint2dMath
class Constraint2dMath
{
public:
  
  static float Dot(const Constraint2dVector& lhs, const Constraint2dVector& rhs);
  //static Constraint2dVector Multiply(const Constraint2dMass& mass, const )
};

}//namespace Physics2dCore
