#include "Precompiled.hpp"

#include "StaticDynamicBroadphase2dManager.hpp"

#include "SandboxSpatialPartitions/Broadphase2d/IBroadphase2d.hpp"
#include "SandboxSpatialPartitions/SpatialPartitions2d/SpatialPartition2dData.hpp"
#include "SandboxSpatialPartitions/SpatialPartitions2d/SpatialPartition2dKey.hpp"
#include "SandboxSpatialPartitions/Core/SelfQueryResults.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------BasicBroadphase2dManager
BasicBroadphase2dManager::~BasicBroadphase2dManager()
{
  for(size_t i = 0; i < LayerCount; ++i)
    delete mBroadphases[i];
}

void BasicBroadphase2dManager::Add(LayerId layerId, IBroadphase2d* broadphase)
{
  delete mBroadphases[layerId];
  mBroadphases[layerId] = broadphase;
}

Broadphase2dKey BasicBroadphase2dManager::Insert(LayerId layerId, Broadphase2dData& data)
{
  IBroadphase2d* broadphase = GetBroadphase(layerId);
  if(broadphase == nullptr)
    return Broadphase2dKey();
  return broadphase->Insert(data);
}

void BasicBroadphase2dManager::Update(LayerId layerId, Broadphase2dKey& key, Broadphase2dData& data)
{
  IBroadphase2d* broadphase = GetBroadphase(layerId);
  if(broadphase != nullptr)
    broadphase->Update(data, key);
}

void BasicBroadphase2dManager::Remove(LayerId layerId, Broadphase2dKey& key)
{
  IBroadphase2d* broadphase = GetBroadphase(layerId);
  if(broadphase != nullptr)
    broadphase->Remove(key);
}

void BasicBroadphase2dManager::Process(LayerId insertId, LayerId updateId, LayerId removeId, Broadphase2dKey& key, Broadphase2dData& data)
{
  // Remap ids
  insertId = RemapId(insertId);
  updateId = RemapId(updateId);
  removeId = RemapId(removeId);

  // If we insert and remove then just do an update
  if(insertId != LayerId::None && removeId != LayerId::None)
    Update(insertId, key, data);
  // Otherwise just do whatever instruction we were given
  else if(insertId != LayerId::None)
    key = Insert(insertId, data);
  else if(updateId != LayerId::None)
    Update(updateId, key, data);
  else if(insertId != LayerId::None)
    Remove(removeId, key);
}

IBroadphase2d*& BasicBroadphase2dManager::GetBroadphase(LayerId layerId)
{
  return mBroadphases[layerId];
}

void BasicBroadphase2dManager::Raycast(LayerId layerId, const Ray2d& ray, Array<const Collider2d*>& colliderCastResults)
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

void BasicBroadphase2dManager::SelfQuery(LayerId layerId, Array<Collider2dPair>& pairs)
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

BasicBroadphase2dManager::LayerId BasicBroadphase2dManager::RemapId(LayerId layerId) const
{
  // Leave pure static alone but put everything else to Dynamic
  if(layerId == LayerId::None || layerId == LayerId::PureStatic)
    return layerId;
  
  return LayerId::Dynamic;
}

}//namespace Physics2dCore
