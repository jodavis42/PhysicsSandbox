#pragma once

#include "SandboxGeometryStandard.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------Aabb2d
class Aabb2d
{
public:
  static Aabb2d InvalidAabb;
  static Aabb2d FromMinMax(const Vector2& min, const Vector2& max);
  static Aabb2d FromCenterAndHalfExtents(const Vector2& center, const Vector2& halfExtents);
  static Aabb2d BuildInvalidAabb();

  Aabb2d();
  Aabb2d(const Vector2& min, const Vector2& max);

  Vector2 GetCenter() const;  
  Vector2 GetExtents() const;
  Vector2 GetHalfExtents() const;

  Aabb2d Translate(const Vector2& translation) const;
  Aabb2d Transform(const Matrix3& transform) const;

  void Combine(const Vector2& point);
  void Combine(const Aabb2d& rhs);
  static Aabb2d Combine(const Aabb2d& lhs, const Aabb2d& rhs);

  Vector2 Search(const Vector2& direction) const;
  static Vector2 Search(const Vector2& direction, const Vector2& aabbMin, const Vector2& aabbMax);

  Vector2 mMin = Vector2::cZero;
  Vector2 mMax = Vector2::cZero;
};

}//namespace SandboxGeometry
