#pragma once

#include "SandboxGeometryStandard.hpp"

#include "SandboxGeometry/Intersection2d/RayIntersectionPoint2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------RayResult2d
class RayResult2d
{
public:
  RayIntersectionPoint2d& GetPoint(size_t index);
  const RayIntersectionPoint2d& GetPoint(size_t index) const;

  RayIntersectionPoint2d& operator[](size_t index);
  const RayIntersectionPoint2d& operator[](size_t index) const;

  size_t Size() const;

  void TransformPoints(const Matrix2& rotation, const Vector2& translation);

  char mPointCount = 0;
  RayIntersectionPoint2d mPoints[2]{};
};

}//namespace SandboxGeometry
