#include "Precompiled.hpp"

#include "Ray2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------Ray2d
Ray2d::Ray2d()
{

}

Ray2d::Ray2d(const Vector2& start, const Vector2& direction)
  : mStart(start), mDirection(direction)
{

}

Vector2 Ray2d::GetPoint(float t) const
{
  return mStart + mDirection * t;
}

}//namespace SandboxGeometry
