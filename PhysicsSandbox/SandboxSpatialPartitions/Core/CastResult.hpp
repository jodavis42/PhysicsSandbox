#pragma once

#include "SandboxSpatialPartitionsStandard.hpp"

namespace SandboxSpatialPartitionCore
{

//-------------------------------------------------------------------CastResult
template <typename ClientDataType>
class CastResult
{
public:
  using DataType = ClientDataType;

  CastResult() {}
  CastResult(float time, const DataType& clientData)
    : mTime(time), mClientData(clientData)
  {

  }

  DataType mClientData;
  float mTime = 0.0f;
};

}//namespace SandboxSpatialPartition2d
