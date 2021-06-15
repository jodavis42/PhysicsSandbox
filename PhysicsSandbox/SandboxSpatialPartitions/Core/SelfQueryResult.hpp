#pragma once

#include "SandboxSpatialPartitionsStandard.hpp"

namespace SandboxSpatialPartitionCore
{

//-------------------------------------------------------------------SelfQueryResult
template <typename ClientDataType>
class SelfQueryResult
{
public:
  using DataType = ClientDataType;

  SelfQueryResult() {}
  SelfQueryResult(const DataType& clientData0, const DataType& clientData1)
    : mClientData0(clientData0), mClientData1(clientData1)
  {

  }

  DataType mClientData0;
  DataType mClientData1;
};

}//namespace SandboxSpatialPartition2d
