#include "Precompiled.hpp"

#include "Constraint2dMoleculeWalker.hpp"
#include "Constraint2dMolecule.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Constraint2dMoleculeWalker
Constraint2dMoleculeWalker::Constraint2dMoleculeWalker()
{
  Reset(nullptr, 0, 0, 0);
}

Constraint2dMoleculeWalker::Constraint2dMoleculeWalker(void* start, StrideType totalStride, OffsetType offset, size_t totalSize)
{
  Reset(start, totalStride, offset, totalSize);
}

void Constraint2dMoleculeWalker::Reset(void* start, StrideType totalStride, OffsetType offset, size_t totalSize)
{
  mRawBufferStart = static_cast<BufferByte*>(start);
  mRawBuffer = mRawBufferStart + offset;
  mOffset = offset;
  mTotalStride = totalStride;
  mTotalSize = totalSize;
}

void Constraint2dMoleculeWalker::operator++()
{
  mRawBuffer += mTotalStride;
}

void Constraint2dMoleculeWalker::operator--()
{
  mRawBuffer -= mTotalStride;
}

void Constraint2dMoleculeWalker::operator+=(size_t i)
{
  mRawBuffer += mTotalStride * i;
}

void Constraint2dMoleculeWalker::operator-=(size_t i)
{
  mRawBuffer -= mTotalStride * i;
}

Constraint2dMolecule& Constraint2dMoleculeWalker::operator*()
{
  return *mMolecules;
}

Constraint2dMolecule& Constraint2dMoleculeWalker::operator->()
{
  return *mMolecules;
}

Constraint2dMolecule& Constraint2dMoleculeWalker::operator[](size_t i)
{
  BufferByte* buffer = mRawBuffer + mTotalStride * i;
  return *reinterpret_cast<Constraint2dMolecule*>(buffer);
}

}//namespace Physics2dCore
