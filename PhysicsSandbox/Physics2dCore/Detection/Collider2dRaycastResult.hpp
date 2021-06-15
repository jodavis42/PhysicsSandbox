#pragma once

#include "Physics2dCoreStandard.hpp"

#include "SandboxGeometry/Intersection2d/RayResult2d.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Collider2dRaycastResult
class Collider2dRaycastResult : public SandboxGeometry::RayResult2d
{
public:
  const Collider2d* mCollider = nullptr;
};

}//namespace Physics2dCore
