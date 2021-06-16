#pragma once

#include "Physics2dCoreStandard.hpp"

#include "Physics2dCore/Detection/Broadphase/IBroadphase2dManager.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------BasicBroadphase2dManager
class BasicBroadphase2dManager : public IBroadphase2dManager
{
public:
  ~BasicBroadphase2dManager();
  void Add(LayerId layer, IBroadphase2d* broadphase);

  Broadphase2dKey Insert(LayerId layerId, Broadphase2dData& data) override;
  void Update(LayerId layerId, Broadphase2dKey& key, Broadphase2dData& data) override;
  void Remove(LayerId layerId, Broadphase2dKey& key) override;
  void Process(LayerId insertId, LayerId updateId, LayerId removeId, Broadphase2dKey& key, Broadphase2dData& data) override;

  void Raycast(LayerId layerId, const Ray2d& ray, Array<const Collider2d*>& colliderCastResults) override;
  void SelfQuery(LayerId layerId, Array<Collider2dPair>& pairs) override;

  IBroadphase2d*& GetBroadphase(LayerId layerId);

private:
  LayerId RemapId(LayerId layerId) const;

  constexpr static size_t LayerCount = 2;
  IBroadphase2d* mBroadphases[2]{};
};

}//namespace Physics2dCore
