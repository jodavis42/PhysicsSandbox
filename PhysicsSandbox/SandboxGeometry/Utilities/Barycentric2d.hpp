#pragma once

#include "SandboxGeometryStandard.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------Barycentric2d
class Barycentric2d
{
public:
  static bool ComputeCoordinate(const Vector2& point, const Vector2& point0, const Vector2& point1, Vector2& baryCoords);
};

}//namespace SandboxGeometry
