#pragma once

#include "Physics2dCoreStandard.hpp"

namespace Physics2dCore
{

namespace Events
{
DeclareEvent(Collider2dCreated);
DeclareEvent(Collider2dDestroyed);
DeclareEvent(Collider2dPropertyChanged);
DeclareEvent(RigidBody2dCreated);
DeclareEvent(RigidBody2dDestroyed);
DeclareEvent(RigidBody2dPropertyChanged);

}//namespace Events

}//namespace Physics2dCore
