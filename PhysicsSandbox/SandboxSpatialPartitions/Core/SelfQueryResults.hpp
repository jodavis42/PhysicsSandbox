#pragma once

#include "SandboxSpatialPartitionsStandard.hpp"
#include "SandboxSpatialPartitions/Core/SelfQueryResult.hpp"

namespace SandboxSpatialPartitionCore
{

//-------------------------------------------------------------------SelfQueryResults
template <typename ClientDataType>
class SelfQueryResults
{
public:
  using DataType = ClientDataType;
  using ResultType = SelfQueryResult<ClientDataType>;

  SelfQueryResults()
  {
  }

  void Add(const ResultType& pair)
  {
    mResults.PushBack(pair);
  }

  template <typename RangeType>
  void AddRange(RangeType range)
  {
    for(; !range.Empty(); range.PopFront())
      Add(range.Front());
  }

  size_t Size() const
  {
    return mResults.Size();
  }

  ResultType& operator[](size_t index) { return mResults[index]; }
  const ResultType& operator[](size_t index) const { return mResults[index]; }

private:

  Zero::Array<ResultType> mResults;
};

}//namespace SandboxSpatialPartitionCore
