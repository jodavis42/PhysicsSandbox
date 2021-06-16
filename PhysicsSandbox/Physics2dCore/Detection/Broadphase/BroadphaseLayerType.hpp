#pragma once

#include "Physics2dCoreStandard.hpp"

namespace Physics2dCore
{

DeclareEnum5(BroadphaseLayerType, PureStatic, Static, Kinematic, Dynamic, None);

inline unsigned char GetMaskFromBroadphaseLayer(BroadphaseLayerType::Enum layer)
{
  if(layer == BroadphaseLayerType::None)
    return 0;
  return 1 << layer;
}

inline BroadphaseLayerType::Enum GetBroadphaseLayerFromMask(unsigned int mask)
{
  for(int i = 0; i < BroadphaseLayerType::None; ++i)
  {
    if(mask & (1 << i))
      return (BroadphaseLayerType::Enum)i;
  }
  return (BroadphaseLayerType::Enum)BroadphaseLayerType::None;
}

}//namespace Physics2dCore
