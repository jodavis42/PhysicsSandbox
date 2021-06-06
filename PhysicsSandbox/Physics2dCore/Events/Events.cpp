#include "Precompiled.hpp"

#include "Events/Events.hpp"

namespace Physics2dCore
{

namespace Events
{

DefineEvent(Collider2dCreated);
DefineEvent(Collider2dDestroyed);
DefineEvent(Collider2dPropertyChanged);
DefineEvent(RigidBody2dCreated);
DefineEvent(RigidBody2dDestroyed);
DefineEvent(RigidBody2dPropertyChanged);

}//namespace Events

}//namespace Physics2dCore
