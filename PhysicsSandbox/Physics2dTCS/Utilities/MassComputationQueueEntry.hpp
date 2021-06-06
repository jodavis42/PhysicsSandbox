#pragma once

#include "Physics2dStandardTCS.hpp"

namespace Physics2dTCS
{

//-------------------------------------------------------------------MassComputationQueueEntry
/// Queue element for keeping track of pending mass calculations updates needed for a rigid body.
class MassComputationQueueEntry
{
public:
  void Initialize(RigidBody2dTCS* owner);
  void Update(float dt);

  void ComputeMassAndCenterOfMass();

  bool mQueued = false;
  bool mUpdateMassProperties = false;

  RigidBody2dTCS* mRigidBody = nullptr;

  Link<MassComputationQueueEntry> mLink;
};

}//namespace Physics2dTCS
