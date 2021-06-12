#include "Precompiled.hpp"

#include "RayResult2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------RayResult2d
RayIntersectionPoint2d& RayResult2d::GetPoint(size_t index)
{
  return mPoints[index];
}

const RayIntersectionPoint2d& RayResult2d::GetPoint(size_t index) const
{
  return mPoints[index];
}

RayIntersectionPoint2d& RayResult2d::operator[](size_t index)
{
  return GetPoint(index);
}

const RayIntersectionPoint2d& RayResult2d::operator[](size_t index) const
{
  return GetPoint(index);
}

size_t RayResult2d::Size() const
{
  return mPointCount;
}

void RayResult2d::TransformPoints(const Matrix2& rotation, const Vector2& translation)
{
  for(size_t i = 0; i < Size(); ++i)
    mPoints[i].Transform(rotation, translation);
}

}//namespace SandboxGeometry
