#pragma once

#include "Physics2dCoreStandard.hpp"

#include "SandboxGeometry/Intersection2d/Manifold2d.hpp"
#include "Physics2dCore/Utilities/Collider2dPair.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------ContactManifold2d
class ContactManifold2d : public SandboxGeometry::Manifold2d
{
public:
  Collider2dPair mColliders;
};

}//namespace Physics2dCore
