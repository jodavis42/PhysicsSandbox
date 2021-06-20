#pragma once

#include "Physics2dCoreStandard.hpp"

#include "Engine/Component.hpp"

namespace Physics2dCore
{

DeclareEnum3(Physics2dEffectType, Gravity, Drag, Unknown);

//-------------------------------------------------------------------Physics2dEffect
class Physics2dEffect : public Zero::Component
{
public:
  ZilchDeclareType(Physics2dEffect, TypeCopyMode::ReferenceType);

  void Serialize(Zero::Serializer& stream) override;
  void OnAllObjectsCreated(Zero::CogInitializer& initializer) override;
  void OnDestroy(uint flags) override;
  
  Physics2dEffectType::Enum GetEffectType() const;

  bool GetActive() const;
  void SetActive(bool active);

protected:
  bool mActive = true;
  Physics2dEffectType::Enum mEffectType = Physics2dEffectType::Unknown;
};

}//namespace Physics2dCore
