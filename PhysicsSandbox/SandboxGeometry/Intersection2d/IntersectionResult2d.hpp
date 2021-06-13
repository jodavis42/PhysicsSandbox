#pragma once

#include "SandboxGeometryStandard.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------IntersectionResult2d
class IntersectionResult2d
{
public:
  enum class Type { None = -1, Hit = 1};

  IntersectionResult2d();
  IntersectionResult2d(Type type);

  operator bool() const;

  Type mType = Type::None;
};

}//namespace SandboxGeometry
