#include "Precompiled.hpp"

#include "FullBroadphase2dManager.hpp"

#include "SandboxSpatialPartitions/Broadphase2d/IBroadphase2d.hpp"
#include "SandboxSpatialPartitions/SpatialPartitions2d/SpatialPartition2dData.hpp"
#include "SandboxSpatialPartitions/SpatialPartitions2d/SpatialPartition2dKey.hpp"
#include "SandboxSpatialPartitions/Core/SelfQueryResults.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------FullBroadphase2dManager
FullBroadphase2dManager::~FullBroadphase2dManager()
{
  for(size_t i = 0; i < LayerCount; ++i)
    delete mBroadphases[i];
}

void FullBroadphase2dManager::Add(LayerId layerId, IBroadphase2d* broadphase)
{
  delete mBroadphases[layerId];
  mBroadphases[layerId] = broadphase;
}

Broadphase2dKey FullBroadphase2dManager::Insert(LayerId layerId, Broadphase2dData& data)
{
  IBroadphase2d* broadphase = GetBroadphase(layerId);
  if(broadphase == nullptr)
    return Broadphase2dKey();
  return broadphase->Insert(data);
}

void FullBroadphase2dManager::Update(LayerId layerId, Broadphase2dKey& key, Broadphase2dData& data)
{
  IBroadphase2d* broadphase = GetBroadphase(layerId);
  if(broadphase != nullptr)
    broadphase->Update(data, key);
}

void FullBroadphase2dManager::Remove(LayerId layerId, Broadphase2dKey& key)
{
  IBroadphase2d* broadphase = GetBroadphase(layerId);
  if(broadphase != nullptr)
    broadphase->Remove(key);
}

IBroadphase2d*& FullBroadphase2dManager::GetBroadphase(LayerId layerId)
{
  return mBroadphases[layerId];
}

void FullBroadphase2dManager::Raycast(LayerId layerId, const Ray2d& ray, Array<const Collider2d*>& colliderCastResults)
{
  IBroadphase2d* broadphase = GetBroadphase(layerId);
  if(broadphase == nullptr)
    return;

  SandboxBroadphase2d::CastResults results;
  broadphase->Raycast(ray, results);
  for(size_t i = 0; i < results.Size(); ++i)
  {
    Collider2d* collider = static_cast<Collider2d*>(results[i].mClientData);
    colliderCastResults.PushBack(collider);
  }
}

void FullBroadphase2dManager::SelfQuery(LayerId layerId, Array<Collider2dPair>& pairs)
{
  IBroadphase2d* broadphase = GetBroadphase(layerId);
  if(broadphase == nullptr)
    return;

  SandboxBroadphase2d::SelfQueryResults results;
  broadphase->SelfQuery(results);
  for(size_t i = 0; i < results.Size(); ++i)
  {
    Collider2dPair& pair = pairs.PushBack();
    Collider2d* collider0 = static_cast<Collider2d*>(results[i].mClientData0);
    Collider2d* collider1 = static_cast<Collider2d*>(results[i].mClientData1);
    pair.Set(collider0, collider1);
  }
}

}//namespace Physics2dCore
