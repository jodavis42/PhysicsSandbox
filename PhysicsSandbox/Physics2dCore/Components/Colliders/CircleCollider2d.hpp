#pragma once

#include "Physics2dCoreStandard.hpp"

#include "Components/Colliders/Collider2d.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------CircleCollider2d
class CircleCollider2d : public Collider2d
{
public:
  ZilchDeclareType(CircleCollider2d, TypeCopyMode::ReferenceType);
  static String RadiusPropertyName;

  CircleCollider2d();
  void Serialize(Zero::Serializer& stream) override;
  void DebugDraw() override;

  float GetRadius() const;
  void SetRadius(float radius);

private:
  float mRadius;
};

}//namespace Physics2dCore
