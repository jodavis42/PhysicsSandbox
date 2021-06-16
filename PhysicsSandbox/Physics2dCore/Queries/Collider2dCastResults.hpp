#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

#include "Physics2dCore/Queries/SortedResults.hpp"
#include "Physics2dCore/Queries/Collider2dCastResult.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Collider2dCastResults
class Collider2dCastResults
{
public:
  ZilchDeclareType(Collider2dCastResults, TypeCopyMode::ReferenceType);

  void SetBounded(size_t maxBounds);
  void SetUnbounded();

  bool IsBounded() const;
  int Capacity() const;
  int GetSize() const;

  void Add(const Collider2dCastResult& result);

  Collider2dCastResult Get(int index);

  const Collider2dCastResult& operator[](size_t index) const;
  Collider2dCastResult& operator[](size_t index);

  SortedResults<Collider2dCastResult> mResults;
};

}//namespace Physics2dCore
