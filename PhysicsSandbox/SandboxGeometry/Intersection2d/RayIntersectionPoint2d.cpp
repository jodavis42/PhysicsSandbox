#include "Precompiled.hpp"

#include "RayIntersectionPoint2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------RayIntersectionPoint2d
void RayIntersectionPoint2d::Transform(const Matrix2& rotation, const Vector2& translation)
{
  mPoint = Math::Multiply(rotation, mPoint) + translation;
  mNormal = Math::Multiply(rotation, mNormal);
}

}//namespace SandboxGeometry
