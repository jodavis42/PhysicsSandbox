#pragma once

#include "SandboxGeometryStandard.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------ManifoldPoint2d
class ManifoldPoint2d
{
public:
  void Transform(const Matrix2& rotation, const Vector2& translation);
  void Flip();
  void UpdatePenetrationDistance();

  Vector2 mPoints[2]{};
  Vector2 mNormal = Vector2::cZero;
  float mPenetrationDistance = 0.0f;
};

}//namespace SandboxGeometry
