#include "Precompiled.hpp"

#include "ManifoldPoint2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------ManifoldPoint2d
void ManifoldPoint2d::Transform(const Matrix2& rotation, const Vector2& translation)
{
  for(size_t i = 0; i < 2; ++i)
    mPoints[i] = Math::Multiply(rotation, mPoints[i]) + translation;
  mNormal = Math::Multiply(rotation, mNormal);
}

}//namespace SandboxGeometry
