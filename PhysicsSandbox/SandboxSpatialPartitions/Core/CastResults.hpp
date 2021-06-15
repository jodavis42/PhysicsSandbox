#pragma once

#include "SandboxSpatialPartitionsStandard.hpp"
#include "SandboxSpatialPartitions/Core/CastResult.hpp"

namespace SandboxSpatialPartitionCore
{

//-------------------------------------------------------------------CastResults
template <typename ClientDataType>
class CastResults
{
public:
  using DataType = ClientDataType;
  using ResultType = CastResult<ClientDataType>;

  CastResults()
  {
    SetUnbounded();
  }

  CastResults(size_t maxSize)
  {
    SetBounded(maxSize);
  }

  void SetBounded(size_t maxSize)
  {
    mBoundedSize = true;
    maxSize = Math::Max(maxSize, size_t(1));
    mResults.Reserve(maxSize);
  }

  void SetUnbounded()
  {
    mBoundedSize = false;
  }

  void Add(float time, const DataType& data)
  {
    Insert(time, data);
  }

  void Add(const ResultType& item)
  {
    Add(item.mTime, item.mClientData);
  }

  template <typename RangeType>
  void AddRange(RangeType range)
  {
    for(; !range.Empty(); range.PopFront())
      Add(range.Front());
  }

  size_t Size() const
  {
    return mCurrentSize;
  }

  size_t Capacity() const
  {
    return mBoundedSize ? mResults.Size() : static_cast<size_t>(-1);
  }

  ResultType& operator[](size_t index) { return mResults[index]; }
  const ResultType& operator[](size_t index) const { return mResults[index]; }

private:

  void Insert(float time, const DataType& data)
  {
    // Handle empty
    size_t insertPosition = Size();
    if(insertPosition == 0)
    {
      mResults.PushBack(ResultType(time, data));
      ++mCurrentSize;
      return;
    }

    // If the new item is after the last item
    if(mResults[insertPosition - 1].mTime < time)
    {
      // If we're not at capacity just push on the back
      if(insertPosition != Capacity())
      {
        mResults.PushBack(ResultType(time, data));
        ++mCurrentSize;
      }
      // In either case, there's no need to iterate
      return;
    }
    // Else we're before
    else
    {
      // If we're not at capacity, increase our capacity
      if(insertPosition != Capacity())
      {
        ++mCurrentSize;
        mResults.Resize(mCurrentSize);
      }
      // Otherwise, we're before the last item so change our insert position to the last item
      else
        --insertPosition;
    }

    // Find the index to insert, copying up every item that is greater in time than the insert value.
    while(insertPosition != 0 && mResults[insertPosition - 1].mTime < time)
    {
      mResults[insertPosition] = mResults[insertPosition - 1];
      --insertPosition;
    }
    mResults[insertPosition] = ResultType(time, data);
  }

  bool mBoundedSize = true;
  size_t mCurrentSize = 0;
  Zero::Array<ResultType> mResults;
};

}//namespace SandboxSpatialPartition2d
