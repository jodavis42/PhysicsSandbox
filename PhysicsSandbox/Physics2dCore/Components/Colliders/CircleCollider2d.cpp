#include "Precompiled.hpp"

#include "CircleCollider2d.hpp"

#include "Events/PropertyChangedEvent.hpp"
#include "Utilities/Collider2dShapes.hpp"

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

}//namespace Physics2dCore
