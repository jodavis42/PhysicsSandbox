#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2dCore
{

class ContactConstraint2d;

//-------------------------------------------------------------------IConstraint2dSolver
class IConstraint2dSolver
{
public:
  virtual ~IConstraint2dSolver() {};

  virtual void Add(ContactConstraint2d* contactConstraint) abstract;
  virtual void Clear() abstract;

  virtual void Solve(float dt) abstract;
};

}//namespace Physics2dCore
