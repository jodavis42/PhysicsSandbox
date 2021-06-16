#include "Precompiled.hpp"

#include "Collider2dCastResults.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Collider2dCastResults
ZilchDefineType(Collider2dCastResults, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::FromDataOnly);
  ZeroBindDocumented();
  ZilchBindDefaultCopyDestructor();

  ZilchBindGetterProperty(Size);
  ZilchBindMethod(Get);
}

void Collider2dCastResults::SetBounded(size_t maxBounds)
{
  mResults.SetBounded(maxBounds);
}

void Collider2dCastResults::SetUnbounded()
{
  mResults.SetUnbounded();
}

bool Collider2dCastResults::IsBounded() const
{
  return mResults.IsBounded();
}

int Collider2dCastResults::Capacity() const
{
  return mResults.Capacity();
}

int Collider2dCastResults::GetSize() const
{
  return mResults.Size();
}

void Collider2dCastResults::Add(const Collider2dCastResult& result)
{
  mResults.Add(result.mTime, result);
}

Collider2dCastResult Collider2dCastResults::Get(int index)
{
  return mResults[index].mData;
}

const Collider2dCastResult& Collider2dCastResults::operator[](size_t index) const
{
  return mResults[index].mData;
}

Collider2dCastResult& Collider2dCastResults::operator[](size_t index)
{
  return mResults[index].mData;
}

}//namespace Physics2dCore
