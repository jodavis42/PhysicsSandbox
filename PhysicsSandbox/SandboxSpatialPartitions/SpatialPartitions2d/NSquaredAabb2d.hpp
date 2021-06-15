#pragma once

#include "SandboxSpatialPartitionsStandard.hpp"

#include "SpatialPartition2dData.hpp"
#include "SpatialPartition2dKey.hpp"
#include "SandboxSpatialPartitions/Core/SlotArray.hpp"
#include "SandboxSpatialPartitions/Core/CastResult.hpp"
#include "SandboxSpatialPartitions/Core/SelfQueryResult.hpp"
#include "SandboxGeometry/Shapes2d/Ray2d.hpp"
#include "SandboxGeometry/Shapes2d/Aabb2d.hpp"
#include "SandboxGeometry/Intersection2d/BooleanTests2d.hpp"
#include "SandboxGeometry/Intersection2d/RayTests2d.hpp"

namespace SandboxSpatialPartition2d
{

//-------------------------------------------------------------------NSquared2d
template <typename ClientDataType>
class NSquaredAabb2d
{
public:
  using DataType = ClientDataType;
  using SpatialPartitionDataType = SpatialPartition2dData<ClientDataType>;
  using KeyType = SpatialPartition2dKey;
  class Item;
  using SlotArray = SandboxSpatialPartitionCore::SlotArray<Item>;
  using SlotArrayRange = typename SlotArray::Range;
  using CastResultType = typename SandboxSpatialPartitionCore::CastResult<DataType>;
  using SelfQueryResultType = typename SandboxSpatialPartitionCore::SelfQueryResult<DataType>;
  class RaycastRange;
  class SelfQueryRange;

  KeyType Insert(const SpatialPartitionDataType& data)
  {
    size_t index = mData.Add(Item(data.mClientData, data.mAabb));

    SpatialPartition2dKey key;
    key.mSizeTKey = index;
    return key;
  }

  void Update(const SpatialPartitionDataType& data, KeyType& key)
  {
    size_t index = key.mSizeTKey;
    mData[index] = Item(data.mClientData, data.mAabb);
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
    RaycastRange(SlotArrayRange range, const Ray2d& ray)
      : mRange(range), mRay(ray)
    {
      SkipEmpty();
    }

    CastResultType Front()
    {
      return CastResultType(mTime, mRange.Front().mClientData);
    }

    void PopFront()
    {
      mRange.PopFront();
      SkipEmpty();
    }

    bool Empty() const
    {
      return mRange.Empty();
    }

  private:

    void SkipEmpty()
    {
      while(!mRange.Empty() && !RayAabb(mRay, mRange.Front().mAabb, mTime))
        mRange.PopFront();
    }

    bool RayAabb(const Ray2d& ray, const Aabb2d& aabb, float& t)
    {
      SandboxGeometry::RayResult2d points;
      bool result = SandboxGeometry::RayTests2d::RayAabb(ray, aabb, points);
      if(result)
        t = points.GetPoint(0).mTime;
      return result;
    }

    SlotArrayRange mRange;
    Ray2d mRay;
    float mTime;
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
      return SelfQueryResultType(mRange0.Front().mClientData, mRange1.Front().mClientData);
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
      SkipEmptyRanges();
      while(!Empty() && !SandboxGeometry::BooleanTests2d::AabbAabb(mRange0.Front().mAabb, mRange1.Front().mAabb))
      {
        mRange1.PopFront();
        SkipEmptyRanges();
      }
    }
    void SkipEmptyRanges()
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
  struct Item
  {
    Item() {}
    Item(ClientDataType clientData, const Aabb2d& aabb) : mClientData(clientData), mAabb(aabb) {}
    ClientDataType mClientData;
    Aabb2d mAabb;
  };

  SlotArray mData;
};

}//namespace SandboxSpatialPartition2d

