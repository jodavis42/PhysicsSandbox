#pragma once

#include "Physics2dCoreStandard.hpp"

namespace Physics2dCore
{

DeclareEnum3(Collider2dType, Box2d, Circle2d, Unknown);

//-------------------------------------------------------------------Collider2d
class Collider2d : public Zero::Component
{
public:
  ZilchDeclareType(Collider2d, TypeCopyMode::ReferenceType);
  static String GhostPropertyName;
  static String SendsCollisionEventsPropertyName;
  static String MaterialPropertyName;
  static String PositionOffsetPropertyName;
  static String RotationOffsetPropertyName;

  void Serialize(Zero::Serializer& stream) override;
  void Initialize(Zero::CogInitializer& initializer) override;
  void OnDestroy(uint flags = 0) override;

  Collider2dType::Enum GetColliderType() const;

  bool GetGhost() const;
  void SetGhost(bool state);

  bool GetSendsCollisionEvents() const;
  void SetSendsCollisionEvents(bool state);

  Physics2dMaterial* GetMaterial() const;
  void SetMaterial(Physics2dMaterial* material);
  float GetDensity() const;

  Vector2 GetPositionOffset() const;
  void SetPositionOffset(const Vector2& offset);

  float GetRotationOffset() const;
  void SetRotationOffset(float offset);

  Matrix4 GetFullWorldTransform() const;

  virtual Aabb2d GetAabb() const;
  virtual ColliderMassProperties2d ComputeMassProperties() const;

protected:
  void SendPropertyEvent(StringParam propName, int flags);

  Collider2dType::Enum mColliderType = Collider2dType::Unknown;
  bool mGhost = false;
  bool mSendsCollisionEvents = true;
  Vector2 mPositionOffset = Vector2::cZero;
  float mRotationOffset = 0.0f;
  Zilch::HandleOf<Physics2dMaterial> mMaterial;
};

}//namespace Physics2dCore
