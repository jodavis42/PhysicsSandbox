#include "Precompiled.hpp"

#include "IBroadphase2dManager.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------IBroadphase2dManager
void IBroadphase2dManager::Process(LayerId insertId, LayerId updateId, LayerId removeId, Broadphase2dKey& key, Broadphase2dData& data)
{
  if(removeId != BroadphaseLayerType::None)
    Remove(removeId, key);
  if(updateId != BroadphaseLayerType::None)
    Update(updateId, key, data);
  if(insertId != BroadphaseLayerType::None)
    key = Insert(insertId, data);
}

}//namespace Physics2dCore
