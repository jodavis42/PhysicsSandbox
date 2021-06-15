#include "Precompiled.hpp"

#include "Collider2d.hpp"

#include "Events/ComponentCreatedEvent.hpp"
#include "Events/Events.hpp"
#include "Events/PropertyChangedEvent.hpp"
#include "Resources/Physics2dMaterial.hpp"
#include "SandboxGeometry/Shapes2d/Aabb2d.hpp"
#include "Physics2dCore/Utilities/MassProperties2d.hpp"

using namespace Zero;

namespace Physics2dCore
{

String Collider2d::GhostPropertyName = "Ghost";
String Collider2d::SendsCollisionEventsPropertyName = "SendsCollisionEvents";
String Collider2d::MaterialPropertyName = "Material";
String Collider2d::PositionOffsetPropertyName = "PositionOffset";
String Collider2d::RotationOffsetPropertyName = "RotationOffset";

//-------------------------------------------------------------------Collider2d
ZilchDefineType(Collider2d, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindDocumented();
  ZeroBindDependency(Zero::Cog);
  ZeroBindDependency(Zero::Transform);

  ZilchBindGetterSetterProperty(Ghost)->ZeroSerialize(false);
  ZilchBindGetterSetterProperty(SendsCollisionEvents)->ZeroSerialize(true);
  ZilchBindGetterSetterProperty(Material);
  ZilchBindGetterSetterProperty(PositionOffset)->ZeroSerialize(Vector2::cZero);
  ZilchBindGetterSetterProperty(RotationOffset)->ZeroSerialize(Vector2::cZero);
}

void Collider2d::Serialize(Zero::Serializer& stream)
{
  MetaSerializeProperties(this, stream);
}

void Collider2d::Initialize(Zero::CogInitializer& initializer)
{
  ComponentCreatedEvent toSend;
  toSend.mComponent = this;
  GetSpace()->DispatchEvent(Events::Collider2dCreated, &toSend);
}

void Collider2d::OnDestroy(uint flags)
{
  ComponentCreatedEvent toSend;
  toSend.mComponent = this;
  GetSpace()->DispatchEvent(Events::Collider2dDestroyed, &toSend);
}

Collider2dType::Enum Collider2d::GetColliderType() const
{
  return mColliderType;
}

bool Collider2d::GetGhost() const
{
  return mGhost;
}

void Collider2d::SetGhost(bool state)
{
  mGhost = state;
  SendPropertyEvent(GhostPropertyName, PropertyChangedFlags::None);
}

bool Collider2d::GetSendsCollisionEvents() const
{
  return mSendsCollisionEvents;
}

void Collider2d::SetSendsCollisionEvents(bool state)
{
  mSendsCollisionEvents = state;
  SendPropertyEvent(SendsCollisionEventsPropertyName, PropertyChangedFlags::None);
}

Physics2dMaterial* Collider2d::GetMaterial() const
{
  return mMaterial;
}

void Collider2d::SetMaterial(Physics2dMaterial* material)
{
  mMaterial = material;
  SendPropertyEvent(MaterialPropertyName, PropertyChangedFlags::RecomputeMassProperties);
}

float Collider2d::GetDensity() const
{
  if(mMaterial == nullptr)
    return 1;
  return mMaterial->mDensity;
}

Vector2 Collider2d::GetPositionOffset() const
{
  return mPositionOffset;
}

void Collider2d::SetPositionOffset(const Vector2& offset)
{
  mPositionOffset = offset;
  SendPropertyEvent(PositionOffsetPropertyName, PropertyChangedFlags::RecomputeMassProperties | PropertyChangedFlags::UpdateSpatialPartition);
}


float Collider2d::GetRotationOffset() const
{
  return mRotationOffset;
}

void Collider2d::SetRotationOffset(float offset)
{
  mRotationOffset = offset;
  SendPropertyEvent(RotationOffsetPropertyName, PropertyChangedFlags::RecomputeMassProperties | PropertyChangedFlags::UpdateSpatialPartition);
}

Matrix4 Collider2d::GetFullWorldTransform() const
{
  Zero::Transform* transform = GetOwner()->has(Zero::Transform);
  Matrix4 worldTransform = transform->GetWorldMatrix();
  Matrix4 preRotationTransform = Matrix4::GenerateRotation(Vector3(0, 0, 1), mRotationOffset);
  Matrix4 preTranslationTransform = Matrix4::GenerateTranslation(Math::ToVector3(mPositionOffset, 0));

  return Math::Multiply(worldTransform, Math::Multiply(preTranslationTransform, preRotationTransform));
}

Aabb2d Collider2d::GetAabb() const
{
  return Aabb2d();
}

ColliderMassProperties2d Collider2d::ComputeMassProperties() const
{
  return ColliderMassProperties2d();
}

void Collider2d::SendPropertyEvent(StringParam propName, int flags)
{
  if(!IsInitialized())
    return;

  PropertyChangedEvent toSend;
  toSend.mComponent = this;
  toSend.mProperty = ZilchGetDerivedType()->FindProperty(propName, Zilch::FindMemberOptions::None);
  toSend.mPropertyName = propName;
  toSend.mFlags.SetFlag(flags);
  DispatchEvent(Events::Collider2dPropertyChanged, &toSend);
}

}//namespace Physics2dCore
