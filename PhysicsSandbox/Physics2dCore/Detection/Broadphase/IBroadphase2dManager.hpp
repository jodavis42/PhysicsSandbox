#pragma once

#include "Physics2dCoreStandard.hpp"

#include "SandboxSpatialPartitions/Broadphase2d/CoreStructs.hpp"
#include "Physics2dCore/Detection/Broadphase/BroadphaseLayerType.hpp"
#include "Physics2dCore/Utilities/Collider2dPair.hpp"

namespace Physics2dCore
{

using Broadphase2dKey = SandboxBroadphase2d::BroadphaseKey;
using Broadphase2dData = SandboxBroadphase2d::BroadphaseData;

//-------------------------------------------------------------------IBroadphase2dManager
class IBroadphase2dManager
{
public:
  using LayerId = BroadphaseLayerType::Enum;

  virtual Broadphase2dKey Insert(LayerId layerId, Broadphase2dData& data) abstract;
  virtual void Update(LayerId layerId, Broadphase2dKey& key, Broadphase2dData& data) abstract;
  virtual void Remove(LayerId layerId, Broadphase2dKey& key) abstract;
  virtual void Process(LayerId insertId, LayerId updateId, LayerId removeId, Broadphase2dKey& key, Broadphase2dData& data);

  virtual void Raycast(LayerId layer, const Ray2d& ray, Array<const Collider2d*>& colliderCastResults) abstract;
  virtual void SelfQuery(LayerId layer, Array<Collider2dPair>& pairs) abstract;
};

}//namespace Physics2dCore
