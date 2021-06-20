#include "Precompiled.hpp"

#include "Physics2dEffect.hpp"

#include "Events/ComponentCreatedEvent.hpp"
#include "Events/Events.hpp"

namespace Physics2dCore
{

using namespace Zero;

//-------------------------------------------------------------------Physics2dEffect
ZilchDefineType(Physics2dEffect, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();

  ZilchBindGetter(EffectType);
  ZilchBindGetterSetterProperty(Active)->ZeroSerialize(true);
}

void Physics2dEffect::Serialize(Zero::Serializer& stream)
{
  MetaSerializeProperties(this, stream);
}

void Physics2dEffect::OnAllObjectsCreated(Zero::CogInitializer& initializer)
{
  ComponentCreatedEvent toSend;
  toSend.mComponent = this;
  GetSpace()->DispatchEvent(Events::Physics2dEffectCreated, &toSend);
}

void Physics2dEffect::OnDestroy(uint flags)
{
  ComponentCreatedEvent toSend;
  toSend.mComponent = this;
  GetSpace()->DispatchEvent(Events::Physics2dEffectDestroyed, &toSend);
}

Physics2dEffectType::Enum Physics2dEffect::GetEffectType() const
{
  return mEffectType;
}

bool Physics2dEffect::GetActive() const
{
  return mActive;
}

void Physics2dEffect::SetActive(bool active)
{
  mActive = active;
}

}//namespace Physics2dCore
