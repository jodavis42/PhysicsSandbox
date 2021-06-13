#pragma once

#include "Physics2dCoreStandard.hpp"

namespace Physics2dCore
{

class Collider2dPair
{
public:
  void Set(const Collider2d* collider0, const Collider2d* collider1)
  {
    mColliders[0] = collider0;
    mColliders[1] = collider1;
  }
  const Collider2d* operator[](size_t index) { return mColliders[index]; };
  const Collider2d* operator[](size_t index) const { return mColliders[index]; };

  const Collider2d* mColliders[2]{};
};

}//namespace Physics2dCore
