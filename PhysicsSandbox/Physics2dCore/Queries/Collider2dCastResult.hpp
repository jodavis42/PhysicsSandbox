#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Collider2dCastResult
class Collider2dCastResult
{
public:
  ZilchDeclareType(Collider2dCastResult, TypeCopyMode::ReferenceType);

  Collider2dCastResult();
  Collider2dCastResult(float time, Collider2d* collider);
  Collider2dCastResult(float time, const Collider2d* collider);

  Collider2d* mCollider = nullptr;
  float mTime = 0.0f;
};

}//namespace Physics2dCore
