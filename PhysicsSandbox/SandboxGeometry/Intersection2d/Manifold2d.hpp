#pragma once

#include "SandboxGeometryStandard.hpp"

#include "SandboxGeometry/Intersection2d/ManifoldPoint2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------Manifold2d
class Manifold2d
{
public:
  ManifoldPoint2d& operator[](size_t index);
  const ManifoldPoint2d& operator[](size_t index) const;

  size_t Size() const;

  void TransformPoints(const Matrix2& rotation, const Vector2& translation);

  char mPointCount = 0;
  ManifoldPoint2d mPoints[2]{};
};

}//namespace SandboxGeometry
