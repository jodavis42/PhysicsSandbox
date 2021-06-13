#include "Precompiled.hpp"

#include "Circle2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------Circle2d
Circle2d::Circle2d()
{

}

Circle2d::Circle2d(const Vector2& center, float radius)
  : mCenter(center)
  , mRadius(radius)
{

}

Circle2d Circle2d::Transform(const Matrix3& transform) const
{
  // The easiest way to transform a circle is to transform it as an ellipse
  // and then compute the circle of the ellipse. To transform an ellipse,
  // just build the two basis vectors and transform them to world space
  // then we can extract the basis vectors.
  Matrix3 circleBasis = Matrix3::GenerateScale(Math::Vector2(mRadius));
  Matrix3 newCircleBasis = Math::Multiply(transform, circleBasis);
  Vector3 basis0 = newCircleBasis.GetBasis(0);
  Vector3 basis1 = newCircleBasis.GetBasis(1);
  float radius0 = Math::Length(basis0);
  float radius1 = Math::Length(basis1);

  Circle2d result;
  result.mCenter = Math::TransformPoint(transform, mCenter);
  result.mRadius = Math::Max(radius0, radius1);
  return result;
}

Vector2 Circle2d::Search(const Vector2& direction) const
{
  return Search(direction, mCenter, mRadius);
}

Vector2 Circle2d::Search(const Vector2& direction, const Vector2& center, float radius)
{
  return center + direction.Normalized() * radius;
}

}//namespace SandboxGeometry
