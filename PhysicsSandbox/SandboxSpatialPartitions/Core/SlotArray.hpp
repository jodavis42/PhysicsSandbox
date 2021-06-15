#pragma once

#include "SandboxSpatialPartitionsStandard.hpp"

namespace SandboxSpatialPartitionCore
{

//-------------------------------------------------------------------SlotArray
template <typename T>
class SlotArray
{
public:
  using DataType = T;
  using SelfType = SlotArray<DataType>;

  class Range
  {
  public:
    Range(SelfType* slotArray)
    {
      mIndex = 0;
      mSlotArray = slotArray;
      SkipEmpty();
    }

    DataType& Front()
    {
      return mSlotArray->Get(mIndex);
    }

    void PopFront()
    {
      ++mIndex;
      SkipEmpty();
    }

    bool Empty() const
    {
      return !(mIndex < mSlotArray->Size());
    }

  private:
    void SkipEmpty()
    {
      while(!Empty() && mSlotArray->IsEmpty(mIndex))
        ++mIndex;
    }

    size_t mIndex;
    SelfType* mSlotArray;
  };

  size_t Add(const DataType& data)
  {
    size_t index = GetEmptySlotIndex();
    auto&& item = mItems[index];
    item.mData = data;
    // Mark the location as not being free
    item.mEmpty = false;
    return index;
  }

  void Remove(size_t index)
  {
    auto&& item = mItems[index];
    // Mark this location as now being free
    item.mEmpty = true;
    mFreeIndices.PushBack(index);
  }

  size_t Size() const
  {
    return mItems.Size();
  }

  bool IsEmpty(size_t index)
  {
    return mItems[index].mEmpty;
  }

  DataType& Get(size_t index)
  {
    return mItems[index].mData;
  }

  const DataType& Get(size_t index) const
  {
    return mItems[index].mData;
  }

  DataType& operator[](size_t index)
  {
    return Get(index);
  }

  const DataType& operator[](size_t index) const
  {
    return Get(index);
  }
  
  Range All()
  {
    return Range(this);
  }
  
private:
  size_t GetEmptySlotIndex()
  {
    size_t result = 0;
    // Either re-use a free slot or add a new item
    if(!mFreeIndices.Empty())
    {
      result = mFreeIndices.Back();
      mFreeIndices.PopBack();
    }
    else
    {
      result = mItems.Size();
      mItems.PushBack();
    }

    return result;
  }

  struct Item
  {
    DataType mData;
    bool mEmpty = true;
  };

  Zero::Array<Item> mItems;
  Zero::Array<size_t> mFreeIndices;
};

}//namespace SandboxSpatialPartition2d
