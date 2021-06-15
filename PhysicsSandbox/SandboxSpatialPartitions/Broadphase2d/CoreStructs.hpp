#pragma once

#include "SandboxSpatialPartitionsStandard.hpp"

#include "SandboxSpatialPartitions/SpatialPartitions2d/SpatialPartition2dData.hpp"
#include "SandboxSpatialPartitions/SpatialPartitions2d/SpatialPartition2dKey.hpp"
#include "SandboxSpatialPartitions/Core/CastResults.hpp"
#include "SandboxSpatialPartitions/Core/SelfQueryResults.hpp"

namespace SandboxBroadphase2d
{

using ClientDataType = void*;
using BroadphaseData = SandboxSpatialPartition2d::SpatialPartition2dData<ClientDataType>;
using BroadphaseKey = SandboxSpatialPartition2d::SpatialPartition2dKey;
using CastResults = SandboxSpatialPartitionCore::CastResults<ClientDataType>;
using SelfQueryResults = SandboxSpatialPartitionCore::SelfQueryResults<ClientDataType>;

}//namespace SandboxBroadphase2d
