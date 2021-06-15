#pragma once

#include "SandboxSpatialPartitionsStandard.hpp"

namespace SandboxSpatialPartition2d
{

//-------------------------------------------------------------------SpatialPartition2dKey
class SpatialPartition2dKey
{
public:
  SpatialPartition2dKey();

  union
  {
    size_t mSizeTKey;
    void* mVoidKey;
  };
};

}//namespace SandboxSpatialPartition2d
