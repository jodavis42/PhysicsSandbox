#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2dCore
{

class Constraint2dMoleculeWalker;

//-------------------------------------------------------------------IConstraint
class IConstraint
{
public:
  virtual ~IConstraint();

  virtual size_t MoleculeCount() const abstract;
  virtual void ComputeMolecules(Constraint2dMoleculeWalker& molecules) abstract;
  virtual void Store(Constraint2dMoleculeWalker& molecules) abstract;
};

}//namespace Physics2dCore
