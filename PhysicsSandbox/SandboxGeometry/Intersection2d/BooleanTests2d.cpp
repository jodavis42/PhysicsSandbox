#include "Precompiled.hpp"

#include "BooleanTests2d.hpp"

#include "SandboxGeometry/Shapes2d/Aabb2d.hpp"
#include "SandboxGeometry/Shapes2d/Circle2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------BooleanTests2d
bool BooleanTests2d::AabbAabb(const Vector2& min0, const Vector2& max0, const Vector2& min1, const Vector2& max1)
{
  for(size_t axis = 0; axis < 2; ++axis)
  {
    if(max0[axis] < min1[axis] || max1[axis] < min0[axis])
      return false;
  }
  return true;
}

bool BooleanTests2d::AabbAabb(const Aabb2d& aabb0, const Aabb2d& aabb1)
{
  return AabbAabb(aabb0.mMin, aabb0.mMax, aabb1.mMin, aabb1.mMax);
}

bool BooleanTests2d::CircleCircle(const Vector2& center0, float radius0, const Vector2& center1, float radius1)
{
  float radiiSum = radius0 + radius1;
  float radiiSumSq = Math::Sq(radiiSum);
  float distSq = Math::LengthSq(center1 - center0);
  return distSq <= radiiSumSq;
}

bool BooleanTests2d::CircleCircle(const Circle2d& circle0, const Circle2d& circle1)
{
  return CircleCircle(circle0.mCenter, circle0.mRadius, circle1.mCenter, circle1.mRadius);
}

bool BooleanTests2d::Test(const Aabb2d& aabb0, const Aabb2d& aabb1)
{
  return AabbAabb(aabb0, aabb1);
}

bool BooleanTests2d::Test(const Circle2d& circle0, const Circle2d& circle1)
{
  return CircleCircle(circle0, circle1);
}

} //namespace SandboxGeometry
