#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

#include "Physics2dCore/Queries/SortedResults.hpp"
#include "Physics2dCore/Queries/Collider2dCastResult.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Constraint2dMass
class Constraint2dMass
{
public:
  float operator[](size_t index) const;
  float& operator[](size_t index);
  size_t Size() const;

  void Set(float invMass0, float invInertia0, float invMass1, float invInertia1);

  float& InvMass0();
  const float& InvMass0() const;

  float& InvInertia0();
  const float& InvInertia0() const;

  float& InvMass1();
  const float& InvMass1() const;

  float& InvInertia1();
  const float& InvInertia1() const;

private:
  static constexpr size_t Count = 4;
  float mData[Count]{};
};

}//namespace Physics2dCore
