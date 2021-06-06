#include "Precompiled.hpp"

#include "BoxCollider2d.hpp"

#include "Events/PropertyChangedEvent.hpp"
#include "Utilities/Collider2dShapes.hpp"

using namespace Zero;

namespace Physics2dCore
{

String BoxCollider2d::SizePropertyName = "Size";

//-------------------------------------------------------------------BoxCollider2d
ZilchDefineType(BoxCollider2d, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();
  ZeroBindDependency(Zero::Cog);
  ZeroBindDependency(Zero::Transform);

  ZeroBindInterface(Collider2d);

  ZilchBindGetterSetterProperty(Size)->ZeroSerialize(Vector2(1, 1));
}

BoxCollider2d::BoxCollider2d()
{
  mColliderType = Collider2dType::Box2d;
}

void BoxCollider2d::Serialize(Zero::Serializer& stream)
{
  MetaSerializeProperties(this, stream);
}

void BoxCollider2d::DebugDraw()
{
  SandboxGeometry::Obb2d shape = Collider2dShapes::GetShape(*this);
  Vector3 center = Math::ToVector3(shape.mCenter, 0);
  Vector3 halfExtents = Math::ToVector3(shape.mHalfExtents, 0.01f);
  Matrix3 rotation;
  rotation.SetBasis(0, Math::ToVector3(shape.mRotation.GetBasis(0), 0));
  rotation.SetBasis(1, Math::ToVector3(shape.mRotation.GetBasis(1), 0));
  rotation.SetBasis(2, Vector3::cZAxis);
  Zero::gDebugDraw->Add(Zero::Debug::Obb(center, halfExtents, rotation));
}

Vector2 BoxCollider2d::GetSize() const
{
  return mSize;
}

void BoxCollider2d::SetSize(const Vector2& size)
{
  mSize = size;
  SendPropertyEvent(SizePropertyName, PropertyChangedFlags::RecomputeMassProperties | PropertyChangedFlags::UpdateSpatialPartition);
}

}//namespace Physics2dCore
