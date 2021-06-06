#pragma once

#include "Physics2dCoreStandard.hpp"

#include "Physics2dCore/Utilities/MassProperties2d.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------MassComputation
class MassComputation
{
public:
  static void ComputeMassProperties(RigidBody2d& body, const Array<ColliderMassProperties2d>& colliderMasses);
  static void UpdateMassProperties(RigidBody2d& body, const BodyMassProperties2d& bodyMassProperties);
};

}//namespace Physics2dCore
