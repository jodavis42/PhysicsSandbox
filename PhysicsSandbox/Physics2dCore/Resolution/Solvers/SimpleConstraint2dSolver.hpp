#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"


#include "Physics2dCore/Detection/ContactManifold2d.hpp"
#include "Physics2dCore/Resolution/ConstraintMolecules/Constraint2dMolecule.hpp"
#include "Physics2dCore/Resolution/ConstraintUtilities/Constraint2dMass.hpp"
#include "Physics2dCore/Resolution/Solvers/IConstraint2dSolver.hpp"

namespace Physics2dCore
{

class ContactConstraint2d;

//-------------------------------------------------------------------SimpleConstraint2dSolver
class SimpleConstraint2dSolver : public IConstraint2dSolver
{
public:
  virtual ~SimpleConstraint2dSolver();
  void Add(ContactConstraint2d* contactConstraint) override;
  void Clear() override;

  void Solve(float dt) override;

  size_t mIterations = 10;
protected:
  void BuildConstraints();
  void WarmStart(float dt);
  void SolveIteration(float dt);
  void StoreAtoms();

  class ContraintData
  {
  public:
    Constraint2dMolecule mMolecule;
    RigidBody2d* mBody0 = nullptr;
    RigidBody2d* mBody1 = nullptr;
  };
  Zero::Array<ContactConstraint2d*> mContactConstraints;
  Zero::Array<ContraintData> mConstraints;
};

}//namespace Physics2dCore
