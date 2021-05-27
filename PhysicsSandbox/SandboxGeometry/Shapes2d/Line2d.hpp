#pragma once

#include "SandboxGeometryStandard.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------Line2d
class Line2d
{
public:
  Vector2 GetPoint0() const;
  void SetPoint0(const Vector2& point);

  Vector2 GetPoint1() const;
  void SetPoint1(const Vector2& point);

  Vector2 GetPoint(size_t index) const;
  void SetPoint(size_t index, const Vector2& point);

  Vector2 mPoints[2] = {Vector2::cZero, Vector2::cZero};
};

}//namespace SandboxGeometry
