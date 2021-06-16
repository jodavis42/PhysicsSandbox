#include "Precompiled.hpp"

#include "SimpleBroadphase2dManager.hpp"

#include "SandboxSpatialPartitions/Broadphase2d/IBroadphase2d.hpp"
#include "SandboxSpatialPartitions/SpatialPartitions2d/SpatialPartition2dData.hpp"
#include "SandboxSpatialPartitions/SpatialPartitions2d/SpatialPartition2dKey.hpp"
#include "SandboxSpatialPartitions/Core/SelfQueryResults.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------SimpleBroadphase2dManager
SimpleBroadphase2dManager::~SimpleBroadphase2dManager()
{
  delete mBroadphase;
}

void SimpleBroadphase2dManager::Set(IBroadphase2d* broadphase)
{
  delete mBroadphase;
  mBroadphase = broadphase;
}

Broadphase2dKey SimpleBroadphase2dManager::Insert(LayerId layerId, Broadphase2dData& data)
{
  return mBroadphase->Insert(data);
}

void SimpleBroadphase2dManager::Update(LayerId layerId, Broadphase2dKey& key, Broadphase2dData& data)
{
  mBroadphase->Update(data, key);
}

void SimpleBroadphase2dManager::Remove(LayerId layerId, Broadphase2dKey& key)
{
  mBroadphase->Remove(key);
}

void SimpleBroadphase2dManager::Process(LayerId insertId, LayerId updateId, LayerId removeId, Broadphase2dKey& key, Broadphase2dData& data)
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

void SimpleBroadphase2dManager::Raycast(LayerId layer, const Ray2d& ray, Array<const Collider2d*>& colliderCastResults)
{
  IBroadphase2d* broadphase = mBroadphase;
  SandboxBroadphase2d::CastResults results;
  broadphase->Raycast(ray, results);
  for(size_t i = 0; i < results.Size(); ++i)
  {
    Collider2d* collider = static_cast<Collider2d*>(results[i].mClientData);
    colliderCastResults.PushBack(collider);
  }
}

void SimpleBroadphase2dManager::SelfQuery(LayerId layer, Array<Collider2dPair>& pairs)
{
  IBroadphase2d* broadphase = mBroadphase;
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

SimpleBroadphase2dManager::LayerId SimpleBroadphase2dManager::RemapId(LayerId layerId) const
{
  if(layerId == LayerId::None)
    return LayerId::None;
  return LayerId::Dynamic;
}

}//namespace Physics2dCore
