#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

#include "Physics2dCore/Resolution/ConstraintUtilities/ContactConstraint2dManifold.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------ContactConstraint2d
class ContactConstraint2d
{
public:
  ~ContactConstraint2d();

  void LoadManifold(const ContactManifold2d& manifold);
  void LoadManifold(const ContactConstraint2dManifold& contactManifold);

  size_t MoleculeCount() const;
  void ComputeMolecules(Constraint2dMoleculeWalker& molecules);
  void Store(Constraint2dMoleculeWalker& molecules);

  ContactConstraint2dManifold mManifold;
};

}//namespace Physics2dCore
