#pragma once

#include "Physics2dCoreStandard.hpp"

#include "Physics2dCore/Detection/Broadphase/IBroadphase2dManager.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------SimpleBroadphase2dManager
/// A simple broadphase manager that inserts everything into the same broadphase for all categories
class SimpleBroadphase2dManager : public IBroadphase2dManager
{
public:
  ~SimpleBroadphase2dManager();
  void Set(IBroadphase2d* broadphase);

  Broadphase2dKey Insert(LayerId layerId, Broadphase2dData& data) override;
  void Update(LayerId layerId, Broadphase2dKey& key, Broadphase2dData& data) override;
  void Remove(LayerId layerId, Broadphase2dKey& key) override;
  void Process(LayerId insertId, LayerId updateId, LayerId removeId, Broadphase2dKey& key, Broadphase2dData& data) override;

  void Raycast(LayerId layer, const Ray2d& ray, Array<const Collider2d*>& colliderCastResults) override;
  void SelfQuery(LayerId layer, Array<Collider2dPair>& pairs) override;

private:
  LayerId RemapId(LayerId layerId) const;

  IBroadphase2d* mBroadphase = nullptr;
};

}//namespace Physics2dCore
