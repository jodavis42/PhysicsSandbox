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
DefineEvent(Physics2dEffectCreated);
DefineEvent(Physics2dEffectDestroyed);

}//namespace Events

}//namespace Physics2dCore
