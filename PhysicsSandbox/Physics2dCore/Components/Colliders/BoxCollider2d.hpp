#pragma once

#include "Physics2dCoreStandard.hpp"

#include "Components/Colliders/Collider2d.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------BoxCollider2d
class BoxCollider2d : public Collider2d
{
public:
  ZilchDeclareType(BoxCollider2d, TypeCopyMode::ReferenceType);
  static String SizePropertyName;

  BoxCollider2d();
  void Serialize(Zero::Serializer& stream) override;
  void DebugDraw() override;

  Vector2 GetSize() const;
  void SetSize(const Vector2& size);

private:
  Vector2 mSize = Vector2(1, 1);
};

}//namespace Physics2dCore
