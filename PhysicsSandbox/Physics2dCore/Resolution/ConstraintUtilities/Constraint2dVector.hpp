#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Constraint2dVector
class Constraint2dVector
{
public:
  float operator[](size_t index) const;
  float& operator[](size_t index);
  size_t Size() const;

  void Set(const Vector2& linear0, float angular0, const Vector2& linear1, float angular1);

  Vector2& Linear0();
  const Vector2& Linear0() const;

  float& Angular0();
  const float& Angular0() const;

  Vector2& Linear1();
  const Vector2& Linear1() const;

  float& Angular1();
  const float& Angular1() const;

  Constraint2dVector operator+(const Constraint2dVector& rhs) const;
  Constraint2dVector operator-(const Constraint2dVector& rhs) const;
  Constraint2dVector operator*(const Constraint2dVector& rhs) const;
  Constraint2dVector operator/(const Constraint2dVector& rhs) const;

  void operator+=(const Constraint2dVector& rhs);
  void operator-=(const Constraint2dVector& rhs);
  void operator*=(const Constraint2dVector& rhs);
  void operator/=(const Constraint2dVector& rhs);
  
  Constraint2dVector operator*(float scalar);
  Constraint2dVector operator/(float scalar);

private:
  static constexpr size_t Count = 6;
  static constexpr size_t Linear0Start = 0;
  static constexpr size_t Linear1Start = 2;
  static constexpr size_t Angular0Start = 4;
  static constexpr size_t Angular1Start = 5;
  float mData[Count]{};
};

}//namespace Physics2dCore
