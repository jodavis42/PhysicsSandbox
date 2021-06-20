#include "Precompiled.hpp"

#include "Constraint2dMath.hpp"

#include "Jacobian2d.hpp"
#include "Constraint2dVelocity.hpp"
#include "Constraint2dMass.hpp"
#include "Constraint2dVector.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Constraint2dMath
float Constraint2dMath::Dot(const Constraint2dVector& lhs, const Constraint2dVector& rhs)
{
  float result = 0;
  for(size_t i = 0; i < lhs.Size(); ++i)
    result += lhs[i] * rhs[i];
  return result;
}

}//namespace Physics2dCore
