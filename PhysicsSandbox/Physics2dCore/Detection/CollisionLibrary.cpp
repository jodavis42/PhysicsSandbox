#include "Precompiled.hpp"

#include "CollisionLibrary.hpp"

#include "Physics2dCore/Components/Colliders/BoxCollider2d.hpp"
#include "Physics2dCore/Components/Colliders/CircleCollider2d.hpp"
#include "Physics2dCore/Utilities/Collider2dShapes.hpp"
#include "SandboxGeometry/Intersection2d/BooleanTests2d.hpp"
#include "SandboxGeometry/Intersection2d/IntersectionTests2d.hpp"
#include "SandboxGeometry/Intersection2d/PointTests2d.hpp"
#include "SandboxGeometry/Intersection2d/RayTests2d.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------CollisionLibrary
CollisionLibrary::CollisionLibrary()
{
  mCollisionFunctions[Collider2dType::Box2d][Collider2dType::Box2d] = &TestIntersectionGeneric<BoxCollider2d, BoxCollider2d>;
  mCollisionFunctions[Collider2dType::Box2d][Collider2dType::Circle2d] = &TestIntersectionGeneric<BoxCollider2d, CircleCollider2d>;
  mCollisionFunctions[Collider2dType::Circle2d][Collider2dType::Box2d] = &TestIntersectionGeneric<CircleCollider2d, BoxCollider2d>;
  mCollisionFunctions[Collider2dType::Circle2d][Collider2dType::Circle2d] = &TestIntersectionGeneric<CircleCollider2d, CircleCollider2d>;

  mPointFunctions[Collider2dType::Box2d] = &PointCastGeneric<BoxCollider2d>;
  mPointFunctions[Collider2dType::Circle2d] = &PointCastGeneric<CircleCollider2d>;

  mRaycastFunctions[Collider2dType::Box2d] = &RayCastGeneric<BoxCollider2d>;
  mRaycastFunctions[Collider2dType::Circle2d] = &RayCastGeneric<CircleCollider2d>;
}

bool CollisionLibrary::TestIntersection(const Collider2d* collider0, const Collider2d* collider1, ContactManifold2d& manifold)
{
  Collider2dType::Enum collider0Type = collider0->GetColliderType();
  Collider2dType::Enum collider1Type = collider1->GetColliderType();
  return mCollisionFunctions[collider0Type][collider1Type](collider0, collider1, manifold);
}

bool CollisionLibrary::CastPoint(const Vector2& point, const Collider2d* collider)
{
  Collider2dType::Enum colliderType = collider->GetColliderType();
  return mPointFunctions[colliderType](point, collider);
}

bool CollisionLibrary::CastRay(const Ray2d& ray, const Collider2d* collider, RayResult2d& result)
{
  Collider2dType::Enum colliderType = collider->GetColliderType();
  return mRaycastFunctions[colliderType](ray, collider, result);
}

template <typename ColliderType0, typename ColliderType1>
bool CollisionLibrary::TestIntersectionGeneric(const Collider2d* collider0, const Collider2d* collider1, ContactManifold2d& manifold)
{
  const ColliderType0* typedCollider0 = static_cast<const ColliderType0*>(collider0);
  const ColliderType1* typedCollider1 = static_cast<const ColliderType1*>(collider1);
  auto&& shape0 = Collider2dShapes::GetShape(*typedCollider0);
  auto&& shape1 = Collider2dShapes::GetShape(*typedCollider1);

  bool result = SandboxGeometry::IntersectionTests2d::Test(shape0, shape1, manifold);
  if(result)
    manifold.mColliders.Set(collider0, collider1);
  return result;
}

template <typename ColliderType>
static bool CollisionLibrary::PointCastGeneric(const Vector2& point, const Collider2d* collider)
{
  const ColliderType* typedCollider = static_cast<const ColliderType*>(collider);
  auto&& shape = Collider2dShapes::GetShape(*typedCollider);
  return SandboxGeometry::PointTests2d::Test(point, shape);
}

template <typename ColliderType>
static bool CollisionLibrary::RayCastGeneric(const Ray2d& ray, const Collider2d* collider, RayResult2d& result)
{
  const ColliderType* typedCollider = static_cast<const ColliderType*>(collider);
  auto&& shape = Collider2dShapes::GetShape(*typedCollider);
  return SandboxGeometry::RayTests2d::Test(ray, shape, result);
}

}//namespace Physics2dCore
