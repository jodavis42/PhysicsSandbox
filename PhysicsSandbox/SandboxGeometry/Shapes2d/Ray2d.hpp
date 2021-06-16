#pragma once

#include "SandboxGeometryStandard.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------Ray2d
class Ray2d
{
public:
  Ray2d();
  Ray2d(const Vector2& start, const Vector2& direction);

  Vector2 GetPoint(float t) const;

  Vector2 mStart = Vector2::cZero;
  Vector2 mDirection = Vector2::cXAxis;
};

}//namespace SandboxGeometry
