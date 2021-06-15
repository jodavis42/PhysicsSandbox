#pragma once

#include "SandboxSpatialPartitionsStandard.hpp"

#include "SpatialPartition2dData.hpp"
#include "SpatialPartition2dKey.hpp"
#include "SandboxSpatialPartitions/Core/SlotArray.hpp"
#include "SandboxSpatialPartitions/Core/CastResult.hpp"
#include "SandboxSpatialPartitions/Core/SelfQueryResult.hpp"

namespace SandboxSpatialPartition2d
{

//-------------------------------------------------------------------NSquared2d
template <typename ClientDataType>
class NSquared2d
{
public:
  using DataType = ClientDataType;
  using SpatialPartitionDataType = SpatialPartition2dData<ClientDataType>;
  using KeyType = SpatialPartition2dKey;
  using SlotArray = SandboxSpatialPartitionCore::SlotArray<ClientDataType>;
  using SlotArrayRange = typename SlotArray::Range;
  using CastResultType = typename SandboxSpatialPartitionCore::CastResult<DataType>;
  using SelfQueryResultType = typename SandboxSpatialPartitionCore::SelfQueryResult<DataType>;
  class RaycastRange;
  class SelfQueryRange;

  KeyType Insert(const SpatialPartitionDataType& data)
  {
    SpatialPartition2dKey key;
    key.mSizeTKey = mData.Add(data.mClientData);
    return key;
  }

  void Update(const SpatialPartitionDataType& data, KeyType& key)
  {
    size_t index = key.mSizeTKey;
    mData[index] = data.mClientData;
  }

  void Remove(KeyType& key)
  {
    mData.Remove(key.mSizeTKey);
  }

  RaycastRange Raycast(const Ray2d& ray)
  {
    return RaycastRange(mData.All(), ray);
  }

  SelfQueryRange SelfQuery()
  {
    return SelfQueryRange(mData.All());
  }

  class RaycastRange
  {
  public:
    RaycastRange(SlotArrayRange range, const Ray2d& ray) : mRange(range) { }
    CastResultType Front() { return CastResultType(0.0f, mRange.Front()); }
    void PopFront() { mRange.PopFront(); }
    bool Empty() const { return mRange.Empty(); }

  private:

    SlotArrayRange mRange;
  };

  class SelfQueryRange
  {
  public:
    SelfQueryRange(SlotArrayRange range) : mRange0(range), mRange1(range)
    {
      if(Empty())
        return;

      mRange1.PopFront();
      SkipEmpty();
    }

    SelfQueryResultType Front()
    {
      return SelfQueryResultType(mRange0.Front(), mRange1.Front());
    }

    void PopFront()
    {
      mRange1.PopFront();
      SkipEmpty();
    }

    bool Empty() const
    {
      return mRange0.Empty();
    }

  private:

    void SkipEmpty()
    {
      while(mRange1.Empty())
      {
        mRange0.PopFront();
        if(mRange0.Empty())
          break;

        mRange1 = mRange0;
        mRange1.PopFront();
      }
    }

    SlotArrayRange mRange0;
    SlotArrayRange mRange1;
  };
  
private:

  SlotArray mData;
};

}//namespace SandboxSpatialPartition2d
