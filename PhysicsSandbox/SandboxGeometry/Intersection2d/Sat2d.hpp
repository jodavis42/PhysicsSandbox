#pragma once

#include "SandboxGeometryStandard.hpp"

#include "IntersectionResult2d.hpp"

#include "SandboxGeometry/Intersection2d/RayResult2d.hpp"

namespace SandboxGeometry
{

class SatShape2d;

//-------------------------------------------------------------------Sat2d
class Sat2d
{
public:
  bool Test(SatShape2d& shape0, SatShape2d& shape1, Manifold2d& manifold);

private:
  bool TestShape(SatShape2d& primaryShape, SatShape2d& secondaryShape, size_t& minAxis, float& minDistance);
  void BuildManifold(SatShape2d& primaryShape, SatShape2d& incidentShape, size_t minAxis, Manifold2d& manifold);
  size_t FindIncidentFace(SatShape2d& shape, const Vector2& normal);

  Vector2 ClipPointToLine(const Vector2& testPoint, const Vector2& point0, const Vector2& point1);
};

}//namespace SandboxGeometry
