#pragma once

#include "SandboxSpatialPartitionsStandard.hpp"

#include "SandboxGeometry/Shapes2d/Aabb2d.hpp"
#include "SandboxGeometry/Shapes2d/Circle2d.hpp"

namespace SandboxSpatialPartition2d
{

//-------------------------------------------------------------------SpatialPartition2dData
template <typename ClientDataType>
class SpatialPartition2dData
{
public:
  Aabb2d mAabb;
  Circle2d mCircle;
  ClientDataType mClientData;
};

}//namespace SandboxSpatialPartition2d
