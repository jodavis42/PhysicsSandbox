#include "Precompiled.hpp"

#include "CircleCollider2d.hpp"

#include "Events/PropertyChangedEvent.hpp"
#include "Utilities/Collider2dShapes.hpp"
#include "Utilities/MassProperties2d.hpp"

using namespace Zero;

namespace Physics2dCore
{

String CircleCollider2d::RadiusPropertyName = "Radius";

//-------------------------------------------------------------------CircleCollider2d
ZilchDefineType(CircleCollider2d, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();
  ZeroBindDependency(Zero::Cog);
  ZeroBindDependency(Zero::Transform);

  ZeroBindInterface(Collider2d);

  ZilchBindGetterSetterProperty(Radius)->ZeroSerialize(0.5f);
}

CircleCollider2d::CircleCollider2d()
{
  mColliderType = Collider2dType::Circle2d;
}

void CircleCollider2d::Serialize(Zero::Serializer& stream)
{
  MetaSerializeProperties(this, stream);
}

void CircleCollider2d::DebugDraw()
{
  SandboxGeometry::Circle2d shape = Collider2dShapes::GetShape(*this);
  Vector3 center = Math::ToVector3(shape.mCenter, 0);
  Zero::gDebugDraw->Add(Zero::Debug::Circle(center, Vector3::cZAxis, shape.mRadius));
}

float CircleCollider2d::GetRadius() const
{
  return mRadius;
}

void CircleCollider2d::SetRadius(float radius)
{
  mRadius = radius;
  SendPropertyEvent(RadiusPropertyName, PropertyChangedFlags::RecomputeMassProperties | PropertyChangedFlags::UpdateSpatialPartition);
}

Aabb2d CircleCollider2d::GetAabb() const
{
  return Collider2dShapes::GetAabb(*this);
}

ColliderMassProperties2d CircleCollider2d::ComputeMassProperties() const
{
  ColliderMassProperties2d results;
  Circle2d circle2d = Physics2dCore::Collider2dShapes::GetShape(*this);
  results.mArea = 2 * Math::cPi * circle2d.mRadius;
  results.mCenterOfMass = circle2d.mCenter;
  return results;
}

}//namespace Physics2dCore
