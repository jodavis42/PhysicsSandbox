#include "Precompiled.hpp"

#include "Line2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------Line2d
Vector2 Line2d::GetPoint0() const
{
  return GetPoint(0);
}

void Line2d::SetPoint0(const Vector2& point)
{
  SetPoint(0, point);
}

Vector2 Line2d::GetPoint1() const
{
  return GetPoint(1);
}

void Line2d::SetPoint1(const Vector2& point)
{
  SetPoint(1, point);
}

Vector2 Line2d::GetPoint(size_t index) const
{
  return mPoints[index];
}

void Line2d::SetPoint(size_t index, const Vector2& point)
{
  mPoints[index] = point;
}

}//namespace SandboxGeometry
