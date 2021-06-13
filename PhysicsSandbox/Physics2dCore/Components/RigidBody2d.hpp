#pragma once

#include "Physics2dCoreStandard.hpp"

#include "Engine/Component.hpp"

namespace Physics2dCore
{

DeclareEnum2(MassComputationMode, Automatic, Manual);

//-------------------------------------------------------------------RigidBody2d
class RigidBody2d : public Zero::Component
{
public:
  ZilchDeclareType(RigidBody2d, TypeCopyMode::ReferenceType);
  static String MassComputationModePropertyName;
  static String InvMassPropertyName;
  static String InvInertiaPropertyName;
  static String LinearVelocityPropertyName;
  static String AngularVelocityPropertyName;
  static String ForcePropertyName;
  static String TorquePropertyName;
  static String WorldCenterOfMassPropertyName;
  static String WorldRotationPropertyName;
  static String BodyLocalTranslationOffsetPropertyName;

  void Serialize(Zero::Serializer& stream) override;
  void Initialize(Zero::CogInitializer& initializer) override;
  void OnDestroy(uint flags) override;

  MassComputationMode::Enum GetMassComputationMode() const;
  void SetMassComputationMode(MassComputationMode::Enum mode);
  void SetMassComputationModeNoEvent(MassComputationMode::Enum mode);

  float GetInvMass() const;
  void SetInvMass(float invMass);
  void SetInvMassNoEvent(float invMass);

  float GetInvInertia() const;
  void SetInvInertia(float invInertia);
  void SetInvInertiaNoEvent(float invInertia);

  Vector2 GetLinearVelocity() const;
  void SetLinearVelocity(const Vector2& linearVelocity);
  void SetLinearVelocityNoEvent(const Vector2& linearVelocity);

  float GetAngularVelocity() const;
  void SetAngularVelocity(float angularVelocity);
  void SetAngularVelocityNoEvent(float angularVelocity);

  Vector2 GetForce() const;
  void SetForce(const Vector2& force);
  void SetForceNoEvent(const Vector2& force);

  float GetTorque() const;
  void SetTorque(float torque);
  void SetTorqueNoEvent(float torque);

  Vector2 GetWorldCenterOfMass() const;
  void SetWorldCenterOfMass(const Vector2& worldCenterOfMass);
  void SetWorldCenterOfMassNoEvent(const Vector2& worldCenterOfMass);

  float GetWorldRotation() const;
  void SetWorldRotation(float worldRotation);
  void SetWorldRotationNoEvent(float worldRotation);

  Vector2 GetBodyLocalTranslationOffset() const;
  void SetBodyLocalTranslationOffset(const Vector2& translationOffset);
  void SetBodyLocalTranslationOffsetNoEvent(const Vector2& translationOffset);

  Vector2 GetWorldTranslation() const;

protected:
  void SendPropertyEvent(StringParam propName, int flags);

  MassComputationMode::Enum mMassComputationMode = MassComputationMode::Automatic;

  float mInvMass = 1.0f;
  float mInvInertia = 1.0f;

  Vector2 mLinearVelocity = Vector2::cZero;
  float mAngularVelocity = 0.0f;

  Vector2 mForce = Vector2::cZero;
  float mTorque = 0.0f;

  Vector2 mWorldCenterOfMass = Vector2::cZero;
  float mWorldRotation = 0.0f;
  // The location of the transform relative to the center of mass in the body space (center of mass at origin, no rotation)
  Vector2 mBodyLocalTranslationOffset = Vector2::cZero;
};

}//namespace Physics2dCore
