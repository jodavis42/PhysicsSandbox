#pragma once

#include "SandboxGeometryStandard.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------SatShape2d
class SatShape2d
{
public:
  class Face
  {
  public:
    Vector2 mPoints[2]{};
    Vector2 mNormal;
    Vector2 mEdge;
  };

  size_t PointCount() const;
  size_t EdgeCount() const;
  size_t FaceCount() const;

  Vector2 GetPoint(size_t index) const;
  Line2d GetEdge(size_t index) const;
  Vector2 GetNormal(size_t index) const;
  Face GetFace(size_t index) const;
  
  Vector2 Search(const Vector2& direction) const;
  
  Zero::Array<Vector2> mPoints;
};

void BuildObbSatShape2d(const Vector2& obbCenter, const Matrix2& obbRotation, const Vector2& obbHalfExtents, SatShape2d& shape);

}//namespace SandboxGeometry
