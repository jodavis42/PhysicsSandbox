#include "Precompiled.hpp"

#include "Collider2dCastResult.hpp"

#include "Physics2dCore/Components/Colliders/Collider2d.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Collider2dCastResult
ZilchDefineType(Collider2dCastResult, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::FromDataOnly);
  ZeroBindDocumented();
  ZilchBindDefaultCopyDestructor();

  ZilchBindFieldGetter(mCollider);
  ZilchBindFieldGetter(mTime);
}

Collider2dCastResult::Collider2dCastResult()
{

}

Collider2dCastResult::Collider2dCastResult(float time, Collider2d* collider)
  : mTime(time), mCollider(collider)
{
}

Collider2dCastResult::Collider2dCastResult(float time, const Collider2d* collider)
  : mTime(time), mCollider(const_cast<Collider2d*>(collider))
{
}

}//namespace Physics2dCore
