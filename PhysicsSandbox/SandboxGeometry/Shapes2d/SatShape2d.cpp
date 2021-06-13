#include "Precompiled.hpp"

#include "SatShape2d.hpp"

#include "SandboxGeometry/Shapes2d/Line2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------SatShape2d
size_t SatShape2d::PointCount() const
{
  return mPoints.Size();
}

size_t SatShape2d::EdgeCount() const
{
  return PointCount();
}

size_t SatShape2d::FaceCount() const
{
  return EdgeCount();
}

Vector2 SatShape2d::GetPoint(size_t index) const
{
  return mPoints[index];
}

Line2d SatShape2d::GetEdge(size_t index) const
{
  size_t index0 = index;
  size_t index1 = (index + 1) % PointCount();
  Line2d result;
  result.mPoints[0] = GetPoint(index0);
  result.mPoints[1] = GetPoint(index1);
  return result;
}

Vector2 SatShape2d::GetNormal(size_t index) const
{
  Line2d line = GetEdge(index);
  Vector2 edge = line.mPoints[1] - line.mPoints[0];
  Vector2 normal = Vector2(edge.y, -edge.x);
  return Math::Normalized(normal);
}

SatShape2d::Face SatShape2d::GetFace(size_t index) const
{
  Line2d edge = GetEdge(index);
  Face result;
  result.mPoints[0] = edge.mPoints[0];
  result.mPoints[1] = edge.mPoints[1];
  result.mEdge = result.mPoints[1] - result.mPoints[0];
  result.mNormal = Math::Normalized(Vector2(result.mEdge.y, -result.mEdge.x));
  return result;
}

Vector2 SatShape2d::Search(const Vector2& direction) const
{
  float maxDistance = -Math::PositiveMax();
  size_t maxIndex = 0;
  for(size_t i = 0; i < PointCount(); ++i)
  {
    Vector2 point = GetPoint(i);
    float distance = Math::Dot(direction, point);
    if(distance > maxDistance)
    {
      maxDistance = distance;
      maxIndex = i;
    }
  }
  return GetPoint(maxIndex);
}

void BuildObbSatShape2d(const Vector2& obbCenter, const Matrix2& obbRotation, const Vector2& obbHalfExtents, SatShape2d& shape)
{
  shape.mPoints.Resize(4);
  shape.mPoints[0] = obbCenter + obbRotation.GetBasis(0) * obbHalfExtents[0] + obbRotation.GetBasis(1) * obbHalfExtents[1];
  shape.mPoints[1] = obbCenter - obbRotation.GetBasis(0) * obbHalfExtents[0] + obbRotation.GetBasis(1) * obbHalfExtents[1];
  shape.mPoints[2] = obbCenter - obbRotation.GetBasis(0) * obbHalfExtents[0] - obbRotation.GetBasis(1) * obbHalfExtents[1];
  shape.mPoints[3] = obbCenter + obbRotation.GetBasis(0) * obbHalfExtents[0] - obbRotation.GetBasis(1) * obbHalfExtents[1];
}

}//namespace SandboxGeometry
