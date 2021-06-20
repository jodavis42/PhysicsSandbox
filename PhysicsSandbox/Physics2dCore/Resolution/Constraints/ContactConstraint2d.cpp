#include "Precompiled.hpp"

#include "ContactConstraint2d.hpp"

#include "Physics2dCore/Resolution/ConstraintMolecules/Contact2dMolecules.hpp"
#include "Physics2dCore/Resolution/ConstraintMolecules/Constraint2dMolecule.hpp"
#include "Physics2dCore/Resolution/ConstraintMolecules/Constraint2dMoleculeWalker.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------ContactConstraint2d
ContactConstraint2d::~ContactConstraint2d()
{

}

void ContactConstraint2d::LoadManifold(const ContactManifold2d& manifold)
{
  mManifold.Load(manifold);
}

void ContactConstraint2d::LoadManifold(const ContactConstraint2dManifold& contactManifold)
{
  mManifold = contactManifold;
}

size_t ContactConstraint2d::MoleculeCount() const
{
  return Contact2dMolecules::Size(mManifold);
}

void ContactConstraint2d::ComputeMolecules(Constraint2dMoleculeWalker& molecules)
{
  Contact2dMolecules::ComputeMolecules(mManifold, molecules);
}

void ContactConstraint2d::Store(Constraint2dMoleculeWalker& molecules)
{
  for(size_t i = 0; i < mManifold.Size(); ++i)
  {
    mManifold[i].mAccumulatedImpulse[0] = molecules[i * 2].mTotalImpulse;
    mManifold[i].mAccumulatedImpulse[1] = molecules[i * 2 + 1].mTotalImpulse;
  }

  size_t count = MoleculeCount();
  molecules += count;
}

}//namespace Physics2dCore
