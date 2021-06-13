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

void ManifoldPoint2d::Flip()
{
  Math::Swap(mPoints[0], mPoints[1]);
  mNormal *= -1;
}

void ManifoldPoint2d::UpdatePenetrationDistance()
{
  mPenetrationDistance = Math::Dot(mPoints[0] - mPoints[1], mNormal);
}

}//namespace SandboxGeometry
