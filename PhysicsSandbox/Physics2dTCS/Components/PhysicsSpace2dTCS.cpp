#include "Precompiled.hpp"

#include "PhysicsSpace2dTCS.hpp"

#include "Physics2dCore/Components/RigidBody2d.hpp"
#include "Physics2dCore/Components/Effects/Physics2dEffect.hpp"
#include "Physics2dCore/Events/ComponentCreatedEvent.hpp"
#include "Physics2dCore/Events/PropertyChangedEvent.hpp"
#include "Physics2dCore/Events/Events.hpp"
#include "Physics2dCore/Utilities/Integration2d.hpp"
#include "Physics2dCore/Utilities/TransformComputation.hpp"
#include "Physics2dTCS/Components/RigidBody2dTCS.hpp"
#include "Physics2dTCS/Components/Physics2dEffectTCS.hpp"
#include "Physics2dTCS/Resolution/Contact2dCache.hpp"
#include "Engine/Time.hpp"
#include "Engine/Cog.hpp"
#include "SandboxGeometry/Shapes2d/Ray2d.hpp"
#include "Physics2dCore/Detection/Collider2dRaycastResult.hpp"
#include "Physics2dCore/Detection/CollisionLibrary.hpp"
#include "Physics2dCore/Detection/Broadphase/SimpleBroadphase2dManager.hpp"
#include "Physics2dCore/Resolution/Solvers/SimpleConstraint2dSolver.hpp"
#include "SandboxSpatialPartitions/Broadphase2d/NSquaredAabbBroadphase2d.hpp"

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

  ZilchBindOverloadedMethod(Cast, ZilchInstanceOverload(bool, const Vector2&));
  ZilchBindOverloadedMethod(CastResults, ZilchInstanceOverload(Physics2dCore::Collider2dCastResults, const Vector2&));
  ZilchBindOverloadedMethod(CastResults, ZilchInstanceOverload(Physics2dCore::Collider2dCastResults, const Vector2&, int));
  ZilchBindOverloadedMethod(Cast, ZilchInstanceOverload(float, const Ray2d&));
  ZilchBindOverloadedMethod(CastResults, ZilchInstanceOverload(Physics2dCore::Collider2dCastResults, const Ray2d&));
  ZilchBindOverloadedMethod(CastResults, ZilchInstanceOverload(Physics2dCore::Collider2dCastResults, const Ray2d&, int));
}

PhysicsSpace2dTCS::PhysicsSpace2dTCS()
{
  mCollisionLibrary = new Physics2dCore::CollisionLibrary();
  mConstraintSolver = new Physics2dCore::SimpleConstraint2dSolver();
  mContactCache = new Contact2dCache();
}

PhysicsSpace2dTCS::~PhysicsSpace2dTCS()
{
  delete mContactCache;
  delete mConstraintSolver;
  delete mBroadphaseManager;
  delete mCollisionLibrary;
}

void PhysicsSpace2dTCS::Initialize(Zero::CogInitializer& initializer)
{
  ConnectThisTo(GetOwner(), Zero::Events::SystemLogicUpdate, OnSystemLogicUpdate);
  ConnectThisTo(GetOwner(), Physics2dCore::Events::Collider2dCreated, OnCollider2dCreated);
  ConnectThisTo(GetOwner(), Physics2dCore::Events::RigidBody2dCreated, OnRigidBody2dCreated);
  ConnectThisTo(GetOwner(), Physics2dCore::Events::Physics2dEffectCreated, OnPhysics2dEffectCreated);
  ConnectThisTo(GetOwner(), Physics2dCore::Events::Physics2dEffectDestroyed, OnPhysics2dEffectDestroyed);

  auto broadphaseManager = new Physics2dCore::SimpleBroadphase2dManager();
  broadphaseManager->Set(new SandboxBroadphase2d::NSquaredAabbBroadphase2d());
  mBroadphaseManager = broadphaseManager;
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
  DetectCollisions();
  ResolutionPhase(dt);
  IntegrateBodiesPosition(dt);
}

void PhysicsSpace2dTCS::DetectCollisions()
{
  Array<Physics2dCore::Collider2dPair> possiblePairs;
  Broadphase(possiblePairs);
  NarrowPhase(possiblePairs);
}

void PhysicsSpace2dTCS::Broadphase(Array<Physics2dCore::Collider2dPair>& possiblePairs)
{
  mBroadphaseManager->SelfQuery(BroadphaseLayerType::Dynamic, possiblePairs);
}

void PhysicsSpace2dTCS::NarrowPhase(Array<Physics2dCore::Collider2dPair>& possiblePairs)
{
  mContactCache->BeginFrame();
  for(auto&& range = possiblePairs.All(); !range.Empty(); range.PopFront())
  {
    auto&& pair = range.Front();
    Physics2dCore::ContactManifold2d manifold;
    if(mCollisionLibrary->TestIntersection(pair.mColliders[0], pair.mColliders[1], manifold))
    {
      DebugDrawContactManifold(manifold);
      mContactCache->Add(manifold);
    }
  }
  mContactCache->EndFrame();
}

void PhysicsSpace2dTCS::ResolutionPhase(float dt)
{
  for(auto range = mContactCache->GetContacts(); !range.Empty(); range.PopFront())
  {
    mConstraintSolver->Add(&range.Front());
  }

  mConstraintSolver->Solve(dt);
  mConstraintSolver->Clear();
}

void PhysicsSpace2dTCS::UpdateQueues(float dt)
{
  Physics2dQueues::UpdateContext context;
  context.mBroadphaseManager = mBroadphaseManager;
  context.mDt = dt;
  mQueues.Update(context);
}

void PhysicsSpace2dTCS::IntegrateBodiesVelocity(float dt)
{
  for(auto range = mRigidBodies.All(); !range.Empty(); range.PopFront())
  {
    auto&& body = range.Front().mRigidBody2d;

    float invMass = body->GetInvMass();
    float invInertia = body->GetInvInertia();
    Vector2 linearVelocity = body->GetLinearVelocity();
    float angularVelocity = body->GetAngularVelocity();
    Vector2 force = body->GetForce();
    float torque = body->GetTorque();
    
    for(auto&& effectRange = mEffects.All(); !effectRange.Empty(); effectRange.PopFront())
      Physics2dEffectTCS::ComputeForces(*effectRange.Front(), dt, linearVelocity, invMass, force, angularVelocity, invInertia, torque);
    
    Physics2dCore::Integration2d::IntegrateVelocityEuler(dt, invMass, invInertia, force, torque, linearVelocity, angularVelocity);
    body->SetLinearVelocityNoEvent(linearVelocity);
    body->SetAngularVelocityNoEvent(angularVelocity);
    body->SetForce(Vector2::cZero);
    body->SetTorque(0.0f);
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
    for(auto colliderRange = bodyTCS.mColliders.All(); !colliderRange.Empty(); colliderRange.PopFront())
      colliderRange.Front().QueueBroadphaseUpdate();
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

bool PhysicsSpace2dTCS::Cast(const Vector2& point)
{
  Physics2dCore::CollisionLibrary library;
  bool hit = false;
  for(auto&& range = mColliders.All(); !range.Empty(); range.PopFront())
  {
    Collider2d* collider = range.Front().mCollider2d;
    hit |= library.CastPoint(point, collider);
  }
  return hit;
}

Physics2dCore::Collider2dCastResults PhysicsSpace2dTCS::CastResults(const Vector2& point)
{
  Physics2dCore::Collider2dCastResults results;
  CastResultsInternal(point, results);
  return results;
}

Physics2dCore::Collider2dCastResults PhysicsSpace2dTCS::CastResults(const Vector2& point, int maxCount)
{
  Physics2dCore::Collider2dCastResults results;
  results.SetBounded(maxCount);
  CastResultsInternal(point, results);
  return results;
}

void PhysicsSpace2dTCS::CastResultsInternal(const Vector2& point, Physics2dCore::Collider2dCastResults& results)
{
  for(auto&& range = mColliders.All(); !range.Empty(); range.PopFront())
  {
    Collider2d* collider = range.Front().mCollider2d;
    if(mCollisionLibrary->CastPoint(point, collider))
      results.Add(Physics2dCore::Collider2dCastResult(0, collider));
  }
}

float PhysicsSpace2dTCS::Cast(const Ray2d& ray)
{
  float tMin = Math::PositiveMax();
  bool hit = false;
  Array<const Collider2d*> colliders;
  mBroadphaseManager->Raycast(BroadphaseLayerType::Dynamic, ray, colliders);
  for(auto&& range = colliders.All(); !range.Empty(); range.PopFront())
  {
    const Collider2d* collider = range.Front();
    Collider2dRaycastResult castResult;
    if(mCollisionLibrary->CastRay(ray, collider, castResult))
    {
      hit = true;
      tMin = Math::Min(tMin, castResult[0].mTime);
    }
  }
  if(!hit)
    tMin = -1;
  return tMin;
}


Physics2dCore::Collider2dCastResults PhysicsSpace2dTCS::CastResults(const Ray2d& ray)
{
  Physics2dCore::Collider2dCastResults results;
  CastResultsInternal(ray, results);
  return results;
}

Physics2dCore::Collider2dCastResults PhysicsSpace2dTCS::CastResults(const Ray2d& ray, int maxCount)
{
  Physics2dCore::Collider2dCastResults results;
  results.SetBounded(maxCount);
  CastResultsInternal(ray, results);
  return results;
}

void PhysicsSpace2dTCS::CastResultsInternal(const Ray2d& ray, Physics2dCore::Collider2dCastResults& results)
{
  Array<const Collider2d*> colliders;
  mBroadphaseManager->Raycast(BroadphaseLayerType::Dynamic, ray, colliders);
  for(auto&& range = colliders.All(); !range.Empty(); range.PopFront())
  {
    const Collider2d* collider = range.Front();
    Collider2dRaycastResult castResult;
    if(mCollisionLibrary->CastRay(ray, collider, castResult))
      results.Add(Physics2dCore::Collider2dCastResult(castResult.mPoints[0].mTime, collider));
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

void PhysicsSpace2dTCS::OnPhysics2dEffectCreated(Physics2dCore::ComponentCreatedEvent* e)
{
  Physics2dEffect* effect = reinterpret_cast<Physics2dEffect*>(e->mComponent);
  mEffects.PushBack(effect);
}

void PhysicsSpace2dTCS::OnPhysics2dEffectDestroyed(Physics2dCore::ComponentCreatedEvent* e)
{
  Physics2dEffect* effect = reinterpret_cast<Physics2dEffect*>(e->mComponent);
  mEffects.EraseValue(effect);
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

void PhysicsSpace2dTCS::DebugDrawContactManifold(const Physics2dCore::ContactManifold2d& manifold)
{
  for(size_t subFeatureIndex = 0; subFeatureIndex < manifold.ContactSubFeatureContactCount(); ++subFeatureIndex)
  {
    auto&& subFeatureContact = manifold.GetSubFeatureContact(subFeatureIndex);
    for(size_t pointIndex = 0; pointIndex < subFeatureContact.Size(); ++pointIndex)
    {
      auto&& point = subFeatureContact[pointIndex];
      Vector3 p0 = Math::ToVector3(point.mPoints[0]);
      Vector3 p1 = Math::ToVector3(point.mPoints[1]);
      Vector3 n = Math::ToVector3(point.mNormal);
      Zero::gDebugDraw->Add(Zero::Debug::Sphere(p0, 0.01f).Color(Color::Red).OnTop(true));
      Zero::gDebugDraw->Add(Zero::Debug::Sphere(p1, 0.01f).Color(Color::Blue).OnTop(true));
      Zero::gDebugDraw->Add(Zero::Debug::Line(p0, p0 - n * point.mPenetrationDistance).Color(Color::Green).HeadSize(0.01f).OnTop(true));
    }
  }
}

}//namespace Physics2d
