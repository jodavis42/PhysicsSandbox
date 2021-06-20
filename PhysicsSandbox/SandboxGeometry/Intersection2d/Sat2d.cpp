#include "Precompiled.hpp"

#include "Sat2d.hpp"

#include "SandboxGeometry/Shapes2d/SatShape2d.hpp"
#include "SandboxGeometry/Intersection2d/Manifold2d.hpp"
#include "SandboxGeometry/Utilities/Barycentric2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------Sat2d
bool Sat2d::Test(SatShape2d& shape0, SatShape2d& shape1, Manifold2d& manifold)
{
  float minDistance0, minDistance1;
  size_t minAxis0, minAxis1;
  if(!TestShape(shape0, shape1, minAxis0, minDistance0) || !TestShape(shape1, shape0, minAxis1, minDistance1))
    return false;

  auto&& point = manifold[0];
  if(minDistance0 < minDistance1)
  {
    BuildManifold(shape0, shape1, minAxis0, manifold);
  }
  else
  {
    BuildManifold(shape1, shape0, minAxis1, manifold);
    manifold.Flip();
  }

  return true;
}

bool Sat2d::TestShape(SatShape2d& primaryShape, SatShape2d& secondaryShape, size_t& minAxis, float& minDistance)
{
  minDistance = Math::PositiveMax();
  minAxis = 0;
  for(size_t faceIndex = 0; faceIndex < primaryShape.FaceCount(); ++faceIndex)
  {
    SatShape2d::Face primaryFace = primaryShape.GetFace(faceIndex);
    Vector2 otherPoint = secondaryShape.Search(-primaryFace.mNormal);
    float penetrationDistance = Math::Dot(-primaryFace.mNormal, otherPoint - primaryFace.mPoints[0]);
    if(penetrationDistance < 0)
      return false;
    if(penetrationDistance < minDistance)
    {
      minDistance = penetrationDistance;
      minAxis = faceIndex;
    }
  }
  return true;
}

void Sat2d::BuildManifold(SatShape2d& primaryShape, SatShape2d& incidentShape, size_t minAxis, Manifold2d& manifold)
{
  manifold.mPointCount = 0;
  auto&& primaryFace = primaryShape.GetFace(minAxis);
  Vector2 normal = primaryFace.mNormal;

  // Find the incident face
  size_t incidentFaceIndex = FindIncidentFace(incidentShape, normal);
  auto incidentFace = incidentShape.GetFace(incidentFaceIndex);

  // Project the incident face onto the primary face
  Vector2 projectedPoints[2];
  float distances[2];
  for(size_t i = 0; i < 2; ++i)
  {
    distances[i] = Math::Dot(normal, incidentFace.mPoints[i] - primaryFace.mPoints[0]);
    projectedPoints[i] = incidentFace.mPoints[i] - normal * distances[i];
  }
  
  // Clip the incident face, only keeping points that were below the surface
  for(size_t i = 0; i < 2; ++i)
  {
    // If a point was below the surface skip it
    if(distances[i] > 0)
      continue;

    // Clip  the projected incident point against the primary face
    Vector2 clippedPoint = ClipPointToLine(projectedPoints[i], primaryFace.mPoints[0], primaryFace.mPoints[1]);
    // Now unproject the clipped point by computing the barycentric coordinates with respect to the projected line and use those coordinates to unproject
    Vector2 projectedBarycCoords;
    Barycentric2d::ComputeCoordinate(clippedPoint, projectedPoints[0], projectedPoints[1], projectedBarycCoords);
    Vector2 unprojectedPoint = projectedBarycCoords.x * incidentFace.mPoints[0] + projectedBarycCoords.y * incidentFace.mPoints[1];

    // Now we have the point on both features
    auto&& manifoldPoint = manifold[manifold.mPointCount];
    ++manifold.mPointCount;
    manifoldPoint.mNormal = normal;
    manifoldPoint.mPoints[0] = clippedPoint;
    manifoldPoint.mPoints[1] = unprojectedPoint;
    manifoldPoint.UpdatePenetrationDistance();
  }
}

size_t Sat2d::FindIncidentFace(SatShape2d& shape, const Vector2& normal)
{
  // Find the face most anti parallel to the given normal
  size_t index = 0;
  float minCosTheta = 1;
  for(size_t i = 0; i < shape.FaceCount(); ++i)
  {
    auto&& face = shape.GetFace(i);
    float cosTheta = Math::Dot(normal, face.mNormal);
    if(cosTheta < minCosTheta)
    {
      minCosTheta = cosTheta;
      index = i;
    }
  }
  return index;
}

Vector2 Sat2d::ClipPointToLine(const Vector2& testPoint, const Vector2& point0, const Vector2& point1)
{
  Vector2 coords;
  Barycentric2d::ComputeCoordinate(testPoint, point0, point1, coords);
  float v = coords.y;
  v = Math::Clamp(v);
  return point0 + v * (point1 - point0);
}

} //namespace SandboxGeometry
