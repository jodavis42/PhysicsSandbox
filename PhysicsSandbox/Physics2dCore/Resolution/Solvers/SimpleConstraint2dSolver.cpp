#include "Precompiled.hpp"

#include "SimpleConstraint2dSolver.hpp"

#include "Physics2dCore/Components/Colliders/Collider2d.hpp"
#include "Physics2dCore/Resolution/Constraints/ContactConstraint2d.hpp"
#include "Physics2dCore/Resolution/ConstraintUtilities/Body2dInfo.hpp"
#include "Physics2dCore/Resolution/ConstraintUtilities/Constraint2dFragments.hpp"
#include "Physics2dCore/Resolution/ConstraintUtilities/Constraint2dMath.hpp"
#include "Physics2dCore/Resolution/ConstraintUtilities/Constraint2dVelocity.hpp"
#include "Physics2dCore/Resolution/ConstraintMolecules/Constraint2dMolecule.hpp"
#include "Physics2dCore/Resolution/ConstraintMolecules/Constraint2dMoleculeWalker.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------SimpleConstraint2dSolver
SimpleConstraint2dSolver::~SimpleConstraint2dSolver()
{

}

void SimpleConstraint2dSolver::Add(ContactConstraint2d* contactConstraint)
{
  mContactConstraints.PushBack(contactConstraint);
}

void SimpleConstraint2dSolver::Clear()
{
  mContactConstraints.Clear();
  mConstraints.Clear();
}

void SimpleConstraint2dSolver::Solve(float dt)
{
  BuildConstraints();
  WarmStart(dt);
  for(size_t i = 0; i < mIterations; ++i)
    SolveIteration(dt);
  StoreAtoms();
}

void SimpleConstraint2dSolver::BuildConstraints()
{
  // Figure out how many constraints are needed
  size_t totalConstraints = 0;
  for(size_t i = 0; i < mContactConstraints.Size(); ++i)
    totalConstraints += mContactConstraints[i]->MoleculeCount();
  mConstraints.Resize(totalConstraints);

  // Setup the walker
  Constraint2dMoleculeWalker molecules;
  molecules.Reset(mConstraints, 0);

  // Extract all the molecules
  size_t constraintIndex = 0;
  for(size_t i = 0; i < mContactConstraints.Size(); ++i)
  {
    auto&& contactConstraint = mContactConstraints[i];
    // Copy the bodies over for each constraint
    RigidBody2d* body0 = contactConstraint->mManifold.GetRigidBody(0);
    RigidBody2d* body1 = contactConstraint->mManifold.GetRigidBody(1);
    size_t moleculeCount = contactConstraint->MoleculeCount();
    for(size_t j = 0; j < moleculeCount; ++j)
    {
      mConstraints[constraintIndex].mBody0 = body0;
      mConstraints[constraintIndex].mBody1 = body1;
      ++constraintIndex;
    }
    contactConstraint->ComputeMolecules(molecules);
  }
}

void SimpleConstraint2dSolver::WarmStart(float dt)
{
  // Apply the cached total impulse
  for(size_t i = 0; i < mConstraints.Size(); ++i)
  {
    auto&& constraintData = mConstraints[i];
    auto&& molecule = constraintData.mMolecule;
    auto&& jacobian = molecule.mJacobian;
    Body2dInfo body0Info, body1Info;
    body0Info.Load(constraintData.mBody0);
    body1Info.Load(constraintData.mBody1);

    Constraint2dVelocity velocities;
    Constraint2dMass masses;
    Constraint2dFragments::Load(body0Info, body1Info, velocities, masses);

    float impulse = mConstraints[i].mMolecule.mTotalImpulse;
    Constraint2dFragments::ApplyImpulse(velocities, masses, jacobian, impulse);

    body0Info.Store(constraintData.mBody0, velocities.Linear0(), velocities.Angular0());
    body1Info.Store(constraintData.mBody1, velocities.Linear1(), velocities.Angular1());
  }
}

void SimpleConstraint2dSolver::SolveIteration(float dt)
{
  for(size_t i = 0; i < mConstraints.Size(); ++i)
  {
    auto&& constraintData = mConstraints[i];
    auto&& molecule = constraintData.mMolecule;
    auto&& jacobian = molecule.mJacobian;
    Body2dInfo body0Info, body1Info;
    body0Info.Load(constraintData.mBody0);
    body1Info.Load(constraintData.mBody1);

    Constraint2dVelocity velocities;
    Constraint2dMass masses;
    Constraint2dFragments::Load(body0Info, body1Info, velocities, masses);

    float impulse = Constraint2dFragments::ComputeLambda(velocities, masses, molecule);
    Constraint2dFragments::ApplyImpulse(velocities, masses, jacobian, impulse);
    molecule.mTotalImpulse += impulse;

    body0Info.Store(constraintData.mBody0, velocities.Linear0(), velocities.Angular0());
    body1Info.Store(constraintData.mBody1, velocities.Linear1(), velocities.Angular1());
  }
}

void SimpleConstraint2dSolver::StoreAtoms()
{
  Constraint2dMoleculeWalker molecules;
  molecules.Reset(mConstraints, 0);
  for(size_t i = 0; i < mContactConstraints.Size(); ++i)
  {
    auto&& contactConstraint = mContactConstraints[i];
    contactConstraint->Store(molecules);
  }
}

}//namespace Physics2dCore
