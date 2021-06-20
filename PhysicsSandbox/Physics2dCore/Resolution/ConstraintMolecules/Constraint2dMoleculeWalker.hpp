#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2dCore
{

class Constraint2dMolecule;

//-------------------------------------------------------------------Constraint2dMoleculeWalker
class Constraint2dMoleculeWalker
{
public:
  using StrideType = unsigned short;
  using OffsetType = unsigned short;
  using BufferByte = unsigned char;

  Constraint2dMoleculeWalker();
  Constraint2dMoleculeWalker(void* start, StrideType totalStride, OffsetType offset, size_t totalSize);

  void Reset(void* start, StrideType totalStride, OffsetType offset, size_t totalSize);

  template <typename T>
  void Reset(Zero::Array<T>& data, size_t offset)
  {
    size_t elementSize = sizeof(T);
    Reset(data.Data(), elementSize + offset, offset, data.Size() * elementSize);
  }

  void operator++();
  void operator--();
  void operator+=(size_t i);
  void operator-=(size_t i);

  Constraint2dMolecule& operator*();
  Constraint2dMolecule& operator->();
  Constraint2dMolecule& operator[](size_t i);

  union
  {
    BufferByte* mRawBuffer = nullptr;
    Constraint2dMolecule* mMolecules;
  };
  BufferByte* mRawBufferStart = nullptr;

  OffsetType mOffset = 0;
  StrideType mTotalStride = 0;
  size_t mTotalSize = 0;
};

}//namespace Physics2dCore
