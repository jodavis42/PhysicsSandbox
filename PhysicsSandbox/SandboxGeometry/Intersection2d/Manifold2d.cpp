#include "Precompiled.hpp"

#include "Manifold2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------Manifold2d
ManifoldPoint2d& Manifold2d::operator[](size_t index)
{
  return mPoints[index];
}

const ManifoldPoint2d& Manifold2d::operator[](size_t index) const
{
  return mPoints[index];
}

size_t Manifold2d::Size() const
{
  return mPointCount;
}

void Manifold2d::TransformPoints(const Matrix2& rotation, const Vector2& translation)
{
  for(size_t i = 0; i < Size(); ++i)
    mPoints[i].Transform(rotation, translation);
}

void Manifold2d::Flip()
{
  for(size_t i = 0; i < Size(); ++i)
    mPoints[i].Flip();
}

}//namespace SandboxGeometry
