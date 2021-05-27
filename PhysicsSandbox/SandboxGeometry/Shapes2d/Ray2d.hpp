#pragma once

#include "SandboxGeometryStandard.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------Ray2d
class Ray2d
{
public:
  Vector2 GetPoint(float t) const;

  Vector2 mStart = Vector2::cZero;
  Vector2 mDirection = Vector2::cXAxis;
};

}//namespace SandboxGeometry
