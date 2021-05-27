#include "Precompiled.hpp"

#include "Ray2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------Ray2d
Vector2 Ray2d::GetPoint(float t) const
{
  return mStart + mDirection * t;
}

}//namespace SandboxGeometry
