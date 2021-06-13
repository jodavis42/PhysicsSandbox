#include "Precompiled.hpp"

#include "Aabb2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------Aabb2d
Aabb2d Aabb2d::InvalidAabb = Aabb2d::BuildInvalidAabb();

Aabb2d Aabb2d::FromMinMax(const Vector2& min, const Vector2& max)
{
  return Aabb2d(min, max);
}

Aabb2d Aabb2d::FromCenterAndHalfExtents(const Vector2& center, const Vector2& halfExtents)
{
  return Aabb2d(center - halfExtents, center + halfExtents);
}

Aabb2d Aabb2d::BuildInvalidAabb()
{
  return Aabb2d(Vector2(Math::PositiveMax()), Vector2(-Math::PositiveMax()));
}

Aabb2d::Aabb2d()
{
  BuildInvalidAabb();
}

Aabb2d::Aabb2d(const Vector2& min, const Vector2& max)
  : mMin(min), mMax(max)
{

}

Vector2 Aabb2d::GetCenter() const
{
  return (mMax + mMin) * 0.5f;
}

Vector2 Aabb2d::GetExtents() const
{
  return (mMax - mMin);
}

Vector2 Aabb2d::GetHalfExtents() const
{
  return GetExtents() * 0.5f;
}

Aabb2d Aabb2d::Translate(const Vector2& translation) const
{
  return Aabb2d::FromMinMax(mMin + translation, mMax + translation);
}

Aabb2d Aabb2d::Transform(const Matrix3& transform) const
{
  Matrix3 absTransform;
  for(size_t y = 0; y < 3; ++y)
  {
    for(size_t x = 0; x < 3; ++x)
      absTransform[y][x] = Math::Abs(transform[y][x]);
  }

  Vector2 center = GetCenter();
  Vector2 halfExtents = GetHalfExtents();
  center = Math::TransformPoint(transform, center);
  halfExtents = Math::TransformNormal(absTransform, halfExtents);

  return Aabb2d::FromCenterAndHalfExtents(center, halfExtents);
}

void Aabb2d::Combine(const Vector2& point)
{
  mMin = Math::Min(mMin, point);
  mMax = Math::Max(mMax, point);
}

void Aabb2d::Combine(const Aabb2d& rhs)
{
  mMin = Math::Min(mMin, rhs.mMin);
  mMax = Math::Max(mMax, rhs.mMax);
}

Aabb2d Aabb2d::Combine(const Aabb2d& lhs, const Aabb2d& rhs)
{
  Aabb2d result;
  result.mMin = Math::Min(lhs.mMin, rhs.mMin);
  result.mMax = Math::Max(lhs.mMax, rhs.mMax);
  return result;
}

Vector2 Aabb2d::Search(const Vector2& direction) const
{
  return Search(direction, mMin, mMax);
}

Vector2 Aabb2d::Search(const Vector2& direction, const Vector2& aabbMin, const Vector2& aabbMax)
{
  Vector2 result;
  for(size_t i = 0; i < 2; ++i)
  {
    if(direction[i] >= 0)
      result[i] = aabbMax[i];
    else
      result[i] = aabbMin[i];
  }
  return result;
}

} //namespace SandboxGeometry
