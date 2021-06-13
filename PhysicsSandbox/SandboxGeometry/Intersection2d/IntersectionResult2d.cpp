#include "Precompiled.hpp"

#include "IntersectionResult2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------IntersectionResult2d
IntersectionResult2d::IntersectionResult2d()
{

}

IntersectionResult2d::IntersectionResult2d(Type type)
  : mType(type)
{

}

IntersectionResult2d::operator bool() const
{
  return static_cast<int>(mType) >= 0;
}

}//namespace SandboxGeometry
