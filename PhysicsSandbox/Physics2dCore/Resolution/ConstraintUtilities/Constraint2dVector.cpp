#include "Precompiled.hpp"

#include "Constraint2dVector.hpp"

namespace Physics2dCore
{

//-------------------------------------------------------------------Constraint2dVector
float Constraint2dVector::operator[](size_t index) const
{
  return mData[index];
}

float& Constraint2dVector::operator[](size_t index)
{
  return mData[index];
}

size_t Constraint2dVector::Size() const
{
  return Count;
}

void Constraint2dVector::Set(const Vector2& linear0, float angular0, const Vector2& linear1, float angular1)
{
  Linear0() = linear0;
  Linear1() = linear1;
  Angular0() = angular0;
  Angular1() = angular1;
}

Vector2& Constraint2dVector::Linear0()
{
  return *reinterpret_cast<Vector2*>(&mData[Linear0Start]);
}

const Vector2& Constraint2dVector::Linear0() const
{
  return *reinterpret_cast<const Vector2*>(&mData[Linear0Start]);
}

float& Constraint2dVector::Angular0()
{
  return mData[Angular0Start];
}

const float& Constraint2dVector::Angular0() const
{
  return mData[Angular0Start];
}

Vector2& Constraint2dVector::Linear1()
{
  return *reinterpret_cast<Vector2*>(&mData[Linear1Start]);
}

const Vector2& Constraint2dVector::Linear1() const
{
  return *reinterpret_cast<const Vector2*>(&mData[Linear1Start]);
}

float& Constraint2dVector::Angular1()
{
  return mData[Angular1Start];
}

const float& Constraint2dVector::Angular1() const
{
  return mData[Angular1Start];
}

Constraint2dVector Constraint2dVector::operator+(const Constraint2dVector& rhs) const
{
  Constraint2dVector result;
  for(size_t i = 0; i < Count; ++i)
    result[i] = mData[i] + rhs[i];
  return result;
}

Constraint2dVector Constraint2dVector::operator-(const Constraint2dVector& rhs) const
{
  Constraint2dVector result;
  for(size_t i = 0; i < Count; ++i)
    result[i] = mData[i] - rhs[i];
  return result;
}

Constraint2dVector Constraint2dVector::operator*(const Constraint2dVector& rhs) const
{
  Constraint2dVector result;
  for(size_t i = 0; i < Count; ++i)
    result[i] = mData[i] * rhs[i];
  return result;
}

Constraint2dVector Constraint2dVector::operator/(const Constraint2dVector& rhs) const
{
  Constraint2dVector result;
  for(size_t i = 0; i < Count; ++i)
    result[i] = mData[i] / rhs[i];
  return result;
}

void Constraint2dVector::operator+=(const Constraint2dVector& rhs)
{
  for(size_t i = 0; i < Count; ++i)
    mData[i] += rhs[i];
}

void Constraint2dVector::operator-=(const Constraint2dVector& rhs)
{
  for(size_t i = 0; i < Count; ++i)
    mData[i] -= rhs[i];
}

void Constraint2dVector::operator*=(const Constraint2dVector& rhs)
{
  for(size_t i = 0; i < Count; ++i)
    mData[i] *= rhs[i];
}

void Constraint2dVector::operator/=(const Constraint2dVector& rhs)
{
  for(size_t i = 0; i < Count; ++i)
    mData[i] /= rhs[i];
}

Constraint2dVector Constraint2dVector::operator*(float scalar)
{
  Constraint2dVector result;
  for(size_t i = 0; i < Count; ++i)
    result[i] = mData[i] * scalar;
  return result;
}

Constraint2dVector Constraint2dVector::operator/(float scalar)
{
  Constraint2dVector result;
  for(size_t i = 0; i < Count; ++i)
    result[i] = mData[i] / scalar;
  return result;
}

}//namespace Physics2dCore
