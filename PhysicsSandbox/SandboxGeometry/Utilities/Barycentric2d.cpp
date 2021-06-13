#include "Precompiled.hpp"

#include "Barycentric2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------Barycentric2d
bool Barycentric2d::ComputeCoordinate(const Vector2& point, const Vector2& point0, const Vector2& point1, Vector2& baryCoords)
{
  // P = uA + vB
  // 1 = u + v
  // P = uA + (1 - u)B
  // P = uA + B - uB
  // P = u(A - B) + B
  // (P - B) = (A - B) u
  // Dot((P - B), (A - B)), Dot((A - B), (A - B)) u
  // u = Dot((P - B), (A - B)) / Dot((A - B), (A - B))
  Vector2 ab = point0 - point1;
  Vector2 pb = point - point1;
  float denom = Math::Dot(ab, ab);
  if(denom == 0)
    return false;

  baryCoords[0] = Math::Dot(pb, ab) / denom;
  baryCoords[1] = 1.0f - baryCoords[0];
  return 0.0f <= baryCoords[0] && baryCoords[0] <= 1.0f;
}

} //namespace SandboxGeometry
