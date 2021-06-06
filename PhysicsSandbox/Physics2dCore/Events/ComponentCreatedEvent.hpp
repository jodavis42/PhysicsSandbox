#pragma once

#include "Physics2dCoreStandard.hpp"

#include "Meta/Event.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------ComponentCreatedEvent
class ComponentCreatedEvent : public Zero::Event
{
public:
  ZilchDeclareType(ComponentCreatedEvent, TypeCopyMode::ReferenceType);

  Zero::Component* mComponent = nullptr;
};

}//namespace Physics2dCore
