#include "Precompiled.hpp"

#include "RigidBody2d.hpp"

#include "Events/ComponentCreatedEvent.hpp"
#include "Events/Events.hpp"
#include "Events/PropertyChangedEvent.hpp"

#include "Engine/Transform.hpp"

using namespace Zero;

namespace Physics2dCore
{

String RigidBody2d::MassComputationModePropertyName = "MassComputationMode";
String RigidBody2d::InvMassPropertyName = "InvMass";
String RigidBody2d::InvInertiaPropertyName = "InvInertia";
String RigidBody2d::LinearVelocityPropertyName = "LinearVelocity";
String RigidBody2d::AngularVelocityPropertyName = "AngularVelocity";
String RigidBody2d::ForcePropertyName = "Force";
String RigidBody2d::TorquePropertyName = "Torque";
String RigidBody2d::WorldCenterOfMassPropertyName = "WorldCenterOfMass";
String RigidBody2d::WorldRotationPropertyName = "WorldRotation";
String RigidBody2d::BodyLocalTranslationOffsetPropertyName = "BodyLocalTranslationOffset";

//-------------------------------------------------------------------RigidBody2d
ZilchDefineType(RigidBody2d, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();
  ZeroBindDependency(Zero::Cog);
  ZeroBindDependency(Zero::Transform);

  ZilchBindGetterSetterProperty(MassComputationMode)->ZeroSerialize(MassComputationMode::Automatic);
  ZilchBindGetterSetter(InvMass);
  ZilchBindGetterSetter(InvInertia);
  ZilchBindGetterSetterProperty(LinearVelocity)->ZeroSerialize(Vector2::cZero);
  ZilchBindGetterSetterProperty(AngularVelocity)->ZeroSerialize(0.0f);
  ZilchBindGetterSetter(Force);
  ZilchBindGetterSetter(Torque);
  ZilchBindGetterSetter(WorldCenterOfMass);
  ZilchBindGetterSetter(WorldRotation);
  ZilchBindGetterSetter(BodyLocalTranslationOffset);
}

void RigidBody2d::Serialize(Zero::Serializer& stream)
{
  MetaSerializeProperties(this, stream);
}

void RigidBody2d::Initialize(Zero::CogInitializer& initializer)
{
  ComponentCreatedEvent toSend;
  toSend.mComponent = this;
  GetSpace()->DispatchEvent(Events::RigidBody2dCreated, &toSend);
}

void RigidBody2d::OnDestroy(uint flags)
{
  ComponentCreatedEvent toSend;
  toSend.mComponent = this;
  GetSpace()->DispatchEvent(Events::RigidBody2dDestroyed, &toSend);
}

MassComputationMode::Enum RigidBody2d::GetMassComputationMode() const
{
  return mMassComputationMode;
}

void RigidBody2d::SetMassComputationMode(MassComputationMode::Enum mode)
{
  SetMassComputationModeNoEvent(mode);
  SendPropertyEvent(MassComputationModePropertyName, PropertyChangedFlags::RecomputeMassProperties);
}

void RigidBody2d::SetMassComputationModeNoEvent(MassComputationMode::Enum mode)
{
  mMassComputationMode = mode;
}

float RigidBody2d::GetInvMass() const
{
  return mInvMass;
}

void RigidBody2d::SetInvMass(float invMass)
{
  if(GetMassComputationMode() == MassComputationMode::Automatic)
    return;

  SetInvMassNoEvent(invMass);
  SendPropertyEvent(InvMassPropertyName, PropertyChangedFlags::None);
}

void RigidBody2d::SetInvMassNoEvent(float invMass)
{
  if(GetMassComputationMode() == MassComputationMode::Automatic)
    return;

  mInvMass = invMass;
}

float RigidBody2d::GetInvInertia() const
{
  return mInvInertia;
}

void RigidBody2d::SetInvInertia(float invInertia)
{
  if(GetMassComputationMode() == MassComputationMode::Automatic)
    return;

  SetInvInertiaNoEvent(invInertia);
  SendPropertyEvent(InvInertiaPropertyName, PropertyChangedFlags::None);
}

void RigidBody2d::SetInvInertiaNoEvent(float invInertia)
{
  if(GetMassComputationMode() == MassComputationMode::Automatic)
    return;

  mInvInertia = invInertia;
}

Vector2 RigidBody2d::GetLinearVelocity() const
{
  return mLinearVelocity;
}

void RigidBody2d::SetLinearVelocity(const Vector2& linearVelocity)
{
  SetLinearVelocityNoEvent(linearVelocity);
  SendPropertyEvent(LinearVelocityPropertyName, PropertyChangedFlags::None);
}

void RigidBody2d::SetLinearVelocityNoEvent(const Vector2& linearVelocity)
{
  mLinearVelocity = linearVelocity;
}

float RigidBody2d::GetAngularVelocity() const
{
  return mAngularVelocity;
}

void RigidBody2d::SetAngularVelocity(float angularVelocity)
{
  SetAngularVelocityNoEvent(angularVelocity);
  SendPropertyEvent(AngularVelocityPropertyName, PropertyChangedFlags::None);
}

void RigidBody2d::SetAngularVelocityNoEvent(float angularVelocity)
{
  mAngularVelocity = angularVelocity;
}

Vector2 RigidBody2d::GetForce() const
{
  return mForce;
}

void RigidBody2d::SetForce(const Vector2& force)
{
  SetForceNoEvent(force);
  SendPropertyEvent(ForcePropertyName, PropertyChangedFlags::None);
}

void RigidBody2d::SetForceNoEvent(const Vector2& force)
{
  mForce = force;
}

float RigidBody2d::GetTorque() const
{
  return mTorque;
}

void RigidBody2d::SetTorque(float torque)
{
  SetTorqueNoEvent(torque);
  SendPropertyEvent(TorquePropertyName, PropertyChangedFlags::None);
}

void RigidBody2d::SetTorqueNoEvent(float torque)
{
  mTorque = torque;
}

Vector2 RigidBody2d::GetWorldCenterOfMass() const
{
  return mWorldCenterOfMass;
}

void RigidBody2d::SetWorldCenterOfMass(const Vector2& worldCenterOfMass)
{
  SetWorldCenterOfMassNoEvent(worldCenterOfMass);
  SendPropertyEvent(WorldCenterOfMassPropertyName, PropertyChangedFlags::RecomputeMassProperties | PropertyChangedFlags::UpdateSpatialPartition);
}

void RigidBody2d::SetWorldCenterOfMassNoEvent(const Vector2& worldCenterOfMass)
{
  mWorldCenterOfMass = worldCenterOfMass;
}

float RigidBody2d::GetWorldRotation() const
{
  return mWorldRotation;
}

void RigidBody2d::SetWorldRotation(float worldRotation)
{
  SetWorldRotationNoEvent(worldRotation);
  SendPropertyEvent(WorldRotationPropertyName, PropertyChangedFlags::RecomputeMassProperties | PropertyChangedFlags::UpdateSpatialPartition);
}

void RigidBody2d::SetWorldRotationNoEvent(float worldRotation)
{
  mWorldRotation = worldRotation;
}

Vector2 RigidBody2d::GetBodyLocalTranslationOffset() const
{
  return mBodyLocalTranslationOffset;
}

void RigidBody2d::SetBodyLocalTranslationOffset(const Vector2& translationOffset)
{
  SetBodyLocalTranslationOffsetNoEvent(translationOffset);
  SendPropertyEvent(BodyLocalTranslationOffsetPropertyName, PropertyChangedFlags::RecomputeMassProperties | PropertyChangedFlags::UpdateSpatialPartition);
}

void RigidBody2d::SetBodyLocalTranslationOffsetNoEvent(const Vector2& translationOffset)
{
  mBodyLocalTranslationOffset = translationOffset;
}

Vector2 RigidBody2d::GetWorldTranslation() const
{
  Zero::Transform* transform = GetOwner()->has(Zero::Transform);
  return Math::ToVector2(transform->GetWorldTranslation());
}

void RigidBody2d::SendPropertyEvent(StringParam propName, int flags)
{
  if(!IsInitialized())
    return;

  PropertyChangedEvent toSend;
  toSend.mComponent = this;
  toSend.mProperty = ZilchGetDerivedType()->FindProperty(propName, Zilch::FindMemberOptions::None);
  toSend.mPropertyName = propName;
  toSend.mFlags.SetFlag(flags);
  DispatchEvent(Events::RigidBody2dPropertyChanged, &toSend);
}

}//namespace Physics2dCore
