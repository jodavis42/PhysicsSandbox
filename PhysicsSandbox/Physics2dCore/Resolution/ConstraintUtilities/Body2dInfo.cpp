#include "Precompiled.hpp"

#include "Body2dInfo.hpp"


#include "Physics2dCore/Components/Colliders/Collider2d.hpp"
#include "Physics2dCore/Components/RigidBody2d.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Body2dInfo
void Body2dInfo::Load(const Collider2d* collider)
{
  if(collider == nullptr)
  {
    Reset();
    return;
  }

  const RigidBody2d* body = collider->GetOwner()->has(RigidBody2d);
  Load(body);
}

void Body2dInfo::Load(const RigidBody2d* body)
{
  if(body == nullptr)
  {
    Reset();
    return;
  }

  mInvMass = body->GetInvMass();
  mInvInertia = body->GetInvInertia();
  mCenterOfMass = body->GetWorldCenterOfMass();
  mRotation = body->GetWorldRotation();
  mLinearVelocity = body->GetLinearVelocity();
  mAngularVelocity = body->GetAngularVelocity();
}

void Body2dInfo::Store(RigidBody2d* body, const Vector2& linearVelocity, float angularVelocity)
{
  if(body != nullptr)
  {
    body->SetLinearVelocityNoEvent(linearVelocity);
    body->SetAngularVelocityNoEvent(angularVelocity);
  }
}

void Body2dInfo::Reset()
{
  mInvMass = 0;
  mInvInertia = 0;
  mCenterOfMass = Vector2::cZero;
  mRotation = 0;
  mLinearVelocity = Vector2::cZero;
  mAngularVelocity = 0;
}

}//namespace Physics2dCore
