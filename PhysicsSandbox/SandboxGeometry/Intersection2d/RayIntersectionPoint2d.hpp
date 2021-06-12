#pragma once

#include "SandboxGeometryStandard.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------RayIntersectionPoint2d
class RayIntersectionPoint2d
{
public:
  using SubFeatureId = size_t;
  static constexpr SubFeatureId InvalidSubFeature = static_cast<SubFeatureId>(-1);

  void Transform(const Matrix2& rotation, const Vector2& translation);

  float mTime = 0.0f;
  Vector2 mPoint = Vector2::cZero;
  Vector2 mNormal = Vector2::cZero;
  SubFeatureId mSubFeatureId = InvalidSubFeature;
};

}//namespace SandboxGeometry
