#pragma once

#include "Physics2dCoreStandard.hpp"

#include "SandboxGeometry/Shapes2d/Circle2d.hpp"
#include "SandboxGeometry/Shapes2d/Obb2d.hpp"
#include "SandboxGeometry/Shapes2d/Aabb2d.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Collider2dShapes
class Collider2dShapes
{
public:
  static SandboxGeometry::Obb2d GetShape(const BoxCollider2d& collider);
  static SandboxGeometry::Circle2d GetShape(const CircleCollider2d& collider);

  static SandboxGeometry::Aabb2d GetAabb(const BoxCollider2d& collider);
  static SandboxGeometry::Aabb2d GetAabb(const CircleCollider2d& collider);
};

}//namespace Physics2dCore
