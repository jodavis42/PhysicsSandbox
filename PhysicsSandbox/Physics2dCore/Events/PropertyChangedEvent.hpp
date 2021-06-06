#pragma once

#include "Physics2dCoreStandard.hpp"

#include "Meta/Event.hpp"

#include "Events/Events.hpp"

namespace Physics2dCore
{

DeclareBitField2(PropertyChangedFlags, RecomputeMassProperties, UpdateSpatialPartition)

//-------------------------------------------------------------------PropertyChangedEvent
class PropertyChangedEvent : public Zero::Event
{
public:
  ZilchDeclareType(PropertyChangedEvent, TypeCopyMode::ReferenceType);

  Zero::BitField<PropertyChangedFlags::Enum> mFlags;
  Zero::Component* mComponent = nullptr;
  Zilch::Property* mProperty = nullptr;
  String mPropertyName;
};

}//namespace Physics2dCore
