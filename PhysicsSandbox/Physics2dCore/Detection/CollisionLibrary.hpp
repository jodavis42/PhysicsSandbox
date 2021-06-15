#pragma once

#include "Physics2dCoreStandard.hpp"

#include "SandboxGeometry/Intersection2d/Manifold2d.hpp"
#include "Physics2dCore/Detection/ContactManifold2d.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------CollisionLibrary
class CollisionLibrary
{
public:
  CollisionLibrary();
  bool TestIntersection(const Collider2d* collider0, const Collider2d* collider1, ContactManifold2d& manifold);

  bool CastPoint(const Vector2& point, const Collider2d* collider0);
  bool CastRay(const Ray2d& ray, const Collider2d* collider, Collider2dRaycastResult& raycastResult);

private:
  template <typename ColliderType0, typename ColliderType1>
  static bool TestIntersectionGeneric(const Collider2d* collider0, const Collider2d* collider1, ContactManifold2d& manifold);

  template <typename ColliderType>
  static bool PointCastGeneric(const Vector2& point, const Collider2d* collider);

  template <typename ColliderType>
  static bool RayCastGeneric(const Ray2d& ray, const Collider2d* collider, Collider2dRaycastResult& result);

  typedef bool (*CollisionFunction)(const Collider2d* collider0, const Collider2d* collider1, ContactManifold2d& manifold);
  CollisionFunction mCollisionFunctions[2][2]{};

  typedef bool (*PointTestFunction)(const Vector2& point, const Collider2d* collider);
  PointTestFunction mPointFunctions[2]{};

  typedef bool (*RaycastFunction)(const Ray2d& ray, const Collider2d* collider, Collider2dRaycastResult& raycastResult);
  RaycastFunction mRaycastFunctions[2]{};
};

}//namespace Physics2dCore
