#include "Precompiled.hpp"

#include "Plane2d.hpp"

namespace SandboxGeometry
{

//-------------------------------------------------------------------Plane2d
Plane2d::Plane2d()
{

}

Plane2d::Plane2d(const Vector3& data)
  : mData(data)
{

}

Plane2d Plane2d::From2Points(const Vector2& p0, const Vector2& p1)
{
  Vector2 edge = p1 - p0;
  Vector2 normal = Vector2(edge.y, -edge.x);
  return FromPointAndNormal(p0, normal);
}

Plane2d Plane2d::FromPointAndNormal(const Vector2& point, const Vector2& normal)
{
  Vector2 n = Math::AttemptNormalized(normal);
  return Plane2d(Vector3(n.x, n.y, Math::Dot(point, normal)));
}

Vector2 Plane2d::GetNormal() const
{
  return Math::ToVector2(mData);
}

float Plane2d::GetDistance() const
{
  return mData.z;
}

Vector3 Plane2d::GetData() const
{
  return mData;
}

}//namespace SandboxGeometry
