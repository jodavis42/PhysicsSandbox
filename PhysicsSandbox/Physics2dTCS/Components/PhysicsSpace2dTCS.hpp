#pragma once

#include "Physics2dStandardTCS.hpp"

#include "Components/Collider2dTCS.hpp"
#include "Components/RigidBody2dTCS.hpp"
#include "Physics2dTCS/Utilities/Physics2dQueues.hpp"
#include "Physics2dCore/Queries/Collider2dCastResults.hpp"

namespace Physics2dCore
{
class ComponentCreatedEvent;
class CollisionLibrary;
}//namespace Physics2dCore

namespace Physics2dTCS
{

//-------------------------------------------------------------------PhysicsSpace2dTCS
class PhysicsSpace2dTCS : public Zero::Component
{
public:
  ZilchDeclareType(PhysicsSpace2dTCS, TypeCopyMode::ReferenceType);

  PhysicsSpace2dTCS();
  ~PhysicsSpace2dTCS();
  void Initialize(Zero::CogInitializer& initializer);
  void OnSystemLogicUpdate(Zero::UpdateEvent* updateEvent);

  void IterateTimestep(float dt);
  void UpdateQueues(float dt);
  void IntegrateBodiesVelocity(float dt);
  void DetectCollisions();
  void Broadphase(Array<Physics2dCore::Collider2dPair>& possiblePairs);
  void NarrowPhase(Array<Physics2dCore::Collider2dPair>& possiblePairs);
  void IntegrateBodiesPosition(float dt);
  void Publish();

  bool Cast(const Vector2& point);
  Physics2dCore::Collider2dCastResults CastResults(const Vector2& point);
  Physics2dCore::Collider2dCastResults CastResults(const Vector2& point, int maxCount);
  void CastResultsInternal(const Vector2& point, Physics2dCore::Collider2dCastResults& results);

  float Cast(const Ray2d& ray);
  Physics2dCore::Collider2dCastResults CastResults(const Ray2d& ray);
  Physics2dCore::Collider2dCastResults CastResults(const Ray2d& ray, int maxCount);
  void CastResultsInternal(const Ray2d& ray, Physics2dCore::Collider2dCastResults& results);

  void OnCollider2dCreated(Physics2dCore::ComponentCreatedEvent* e);
  void OnRigidBody2dCreated(Physics2dCore::ComponentCreatedEvent* e);

  void Add(RigidBody2dTCS* rigidBody);
  void Remove(RigidBody2dTCS* rigidBody);
  void Add(Collider2dTCS* collider);
  void Remove(Collider2dTCS* collider);
  void QueueMassUpdate(RigidBody2dTCS* rigidBody);
  void QueueBroadphaseUpdate(Collider2dTCS* collider);

  void DebugDrawContactManifold(const Physics2dCore::ContactManifold2d& manifold);

  BaseInList<RigidBody2dTCS, RigidBody2dTCS, &RigidBody2dTCS::mSpaceLink> mRigidBodies;
  BaseInList<Collider2dTCS, Collider2dTCS, &Collider2dTCS::mSpaceLink> mColliders;
  Physics2dQueues mQueues;
  Physics2dCore::IBroadphase2dManager* mBroadphaseManager = nullptr;
  Physics2dCore::CollisionLibrary* mCollisionLibrary;
};

}//namespace Physics2d
