#pragma once

#include "Physics2dCoreStandard.hpp"

#include "Physics2dCore/Detection/Broadphase/IBroadphase2dManager.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------FullBroadphase2dManager
class FullBroadphase2dManager : public IBroadphase2dManager
{
public:
  ~FullBroadphase2dManager();
  void Add(LayerId layer, IBroadphase2d* broadphase);

  Broadphase2dKey Insert(LayerId layerId, Broadphase2dData& data) override;
  void Update(LayerId layerId, Broadphase2dKey& key, Broadphase2dData& data) override;
  void Remove(LayerId layerId, Broadphase2dKey& key) override;

  void Raycast(LayerId layerId, const Ray2d& ray, Array<const Collider2d*>& colliderCastResults) override;
  void SelfQuery(LayerId layerId, Array<Collider2dPair>& pairs) override;

  IBroadphase2d*& GetBroadphase(LayerId layerId);

private:
  LayerId RemapId(LayerId layerId) const;

  constexpr static size_t LayerCount = 4;
  IBroadphase2d* mBroadphases[LayerCount]{};
};

}//namespace Physics2dCore
