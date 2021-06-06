#include "Precompiled.hpp"

#include "PhysicsSpace2dTCS.hpp"

#include "Physics2dCore/Components/RigidBody2d.hpp"
#include "Physics2dCore/Events/ComponentCreatedEvent.hpp"
#include "Physics2dCore/Events/PropertyChangedEvent.hpp"
#include "Physics2dCore/Events/Events.hpp"
#include "Physics2dCore/Utilities/Integration2d.hpp"
#include "Physics2dCore/Utilities/TransformComputation.hpp"
#include "Physics2dTCS/Components/RigidBody2dTCS.hpp"
#include "Engine/Time.hpp"
#include "Engine/Cog.hpp"

using namespace Zero;

namespace Physics2dTCS
{

//-------------------------------------------------------------------PhysicsSpace2dTCS
ZilchDefineType(PhysicsSpace2dTCS, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();
  ZeroBindDependency(Zero::Space);
}

void PhysicsSpace2dTCS::Initialize(Zero::CogInitializer& initializer)
{
  ConnectThisTo(GetOwner(), Zero::Events::SystemLogicUpdate, OnSystemLogicUpdate);
  ConnectThisTo(GetOwner(), Physics2dCore::Events::Collider2dCreated, OnCollider2dCreated);
  ConnectThisTo(GetOwner(), Physics2dCore::Events::RigidBody2dCreated, OnRigidBody2dCreated);
}

void PhysicsSpace2dTCS::OnSystemLogicUpdate(Zero::UpdateEvent* updateEvent)
{
  IterateTimestep(updateEvent->Dt);
  Publish();
}

void PhysicsSpace2dTCS::IterateTimestep(float dt)
{
  UpdateQueues(dt);
  IntegrateBodiesVelocity(dt);
  IntegrateBodiesPosition(dt);
}

void PhysicsSpace2dTCS::UpdateQueues(float dt)
{
  mQueues.Update(dt);
}

void PhysicsSpace2dTCS::IntegrateBodiesVelocity(float dt)
{
  Vector2 mGravity = Vector2(0, -9.81f);
  for(auto range = mRigidBodies.All(); !range.Empty(); range.PopFront())
  {
    auto&& body = range.Front().mRigidBody2d;
    float invMass = body->GetInvMass();
    Vector2 force = body->GetForce();
    if(invMass != 0.0f)
      force += mGravity / invMass;

    Vector2 linearVelocity = body->GetLinearVelocity();
    float angularVelocity = body->GetAngularVelocity();
    Physics2dCore::Integration2d::IntegrateVelocityEuler(dt, body->GetInvMass(), body->GetInvInertia(), force, body->GetTorque(), linearVelocity, angularVelocity);
    body->SetLinearVelocityNoEvent(linearVelocity);
    body->SetAngularVelocityNoEvent(angularVelocity);
    body->SetForce(Vector2::cZero);
  }
}

void PhysicsSpace2dTCS::IntegrateBodiesPosition(float dt)
{
  for(auto range = mRigidBodies.All(); !range.Empty(); range.PopFront())
  {
    auto&& bodyTCS = range.Front();
    auto&& body = bodyTCS.mRigidBody2d;
    Vector2 worldCenterOfMass = body->GetWorldCenterOfMass();
    float worldRotation = body->GetWorldRotation();
    Physics2dCore::Integration2d::IntegratePositionEuler(dt, body->GetLinearVelocity(), body->GetAngularVelocity(), worldCenterOfMass, worldRotation);
    bodyTCS.UpdateAfterIntegrationInternal(worldCenterOfMass, worldRotation);
  }
}

void PhysicsSpace2dTCS::Publish()
{
  for(auto range = mRigidBodies.All(); !range.Empty(); range.PopFront())
  {
    auto&& body = range.Front();
    Physics2dCore::TransformComputation::UpdateTransform(*body.mRigidBody2d);
  }
}

void PhysicsSpace2dTCS::OnCollider2dCreated(Physics2dCore::ComponentCreatedEvent* e)
{
  Cog* owner = e->mComponent->GetOwner();
  HasOrAdd<Collider2dTCS>(owner);
}

void PhysicsSpace2dTCS::OnRigidBody2dCreated(Physics2dCore::ComponentCreatedEvent* e)
{
  Cog* owner = e->mComponent->GetOwner();
  HasOrAdd<RigidBody2dTCS>(owner);
}

void PhysicsSpace2dTCS::Add(RigidBody2dTCS* rigidBody)
{
  if(rigidBody->mRigidBody2d == nullptr)
  {
    mQueues.mHierarchyBuildingTask.BodyRemoved(rigidBody);
    return;
  }

  mRigidBodies.PushBack(rigidBody);
  mQueues.mHierarchyBuildingTask.BodyAdded(rigidBody);
  QueueMassUpdate(rigidBody);
}

void PhysicsSpace2dTCS::Remove(RigidBody2dTCS* rigidBody)
{
  mRigidBodies.Erase(rigidBody);
  mQueues.mHierarchyBuildingTask.BodyRemoved(rigidBody);
}

void PhysicsSpace2dTCS::Add(Collider2dTCS* collider)
{
  if(collider->mCollider2d == nullptr)
  {
    mQueues.mHierarchyBuildingTask.ColliderRemoved(collider);
    return;
  }

  mColliders.PushBack(collider);
  mQueues.mHierarchyBuildingTask.ColliderAdded(collider);
  QueueBroadphaseUpdate(collider);
}

void PhysicsSpace2dTCS::Remove(Collider2dTCS* collider)
{
  mColliders.Erase(collider);
  mQueues.mHierarchyBuildingTask.ColliderRemoved(collider);
}

void PhysicsSpace2dTCS::QueueMassUpdate(RigidBody2dTCS* rigidBody)
{
  mQueues.Queue(rigidBody->mMassQueueEntry);
}

void PhysicsSpace2dTCS::QueueBroadphaseUpdate(Collider2dTCS* collider)
{
  mQueues.Queue(collider->mBroadphaseQueueEntry);
}

}//namespace Physics2d
