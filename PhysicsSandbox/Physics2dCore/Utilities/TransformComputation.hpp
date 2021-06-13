#pragma once

#include "Physics2dCoreStandard.hpp"

#include "Physics2dCore/Utilities/MassProperties2d.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------TransformComputation
class TransformComputation
{
public:
  static void UpdateTransform(RigidBody2d& body);
  static void UpdateBodyRotation(RigidBody2d& body);
};

}//namespace Physics2dCore
