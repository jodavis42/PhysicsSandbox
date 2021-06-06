#include "Precompiled.hpp"

#include "Physics2dMaterial.hpp"

#include "Physics2dMaterialManager.hpp"

namespace Physics2dCore
{

//----------------------------------------------------------Physics2dMaterial
ZilchDefineType(Physics2dMaterial, builder, type)
{
  //ZeroBindTag(Zero::Tags::Physics);
  ZeroBindDocumented();

  // For runtime clone
  ZilchBindConstructor();

  ZilchBindMethod(CreateRuntime);
  ZilchBindMethod(RuntimeClone);

  ZilchBindGetterSetterProperty(Density);
  ZilchBindFieldProperty(mRestitution)->Add(new Zero::EditorSlider(0, 1, float(0.001f)));
  ZilchBindGetterSetterProperty(Friction);
  ZilchBindFieldProperty(mRestitutionImportance);
  ZilchBindFieldProperty(mFrictionImportance);
  ZilchBindMethod(UpdateAndNotifyIfModified);
}

Physics2dMaterial::Physics2dMaterial()
{
  mModified = false;
}

void Physics2dMaterial::Serialize(Zero::Serializer& stream)
{
  SerializeNameDefault(mRestitution, float(.5f));
  SerializeNameDefault(mStaticFriction, float(.5f));
  SerializeNameDefault(mDynamicFriction, float(.5f));
  SerializeNameDefault(mDensity, float(1.0f));
  SerializeNameDefault(mRestitutionImportance, 0.0f);
  SerializeNameDefault(mFrictionImportance, 0.0f);

  SetFriction(mDynamicFriction);
  SetDensityInternal(mDensity, false);
}

void Physics2dMaterial::ResourceModified()
{
  // If we're already modified we don't need to do any extra logic
  if(mModified)
    return;

  mModified = true;
  Physics2dMaterialManager* manager = (Physics2dMaterialManager*)GetManager();
  Physics2dMaterialManager::Physics2dMaterialReference resourceRef(this);
  manager->mModifiedResources.PushBack(resourceRef);
}

HandleOf<Physics2dMaterial> Physics2dMaterial::CreateRuntime()
{
  return Physics2dMaterialManager::CreateRuntime();
}

HandleOf<Zero::Resource> Physics2dMaterial::Clone()
{
  return RuntimeClone();
}

HandleOf<Physics2dMaterial> Physics2dMaterial::RuntimeClone()
{
  auto&& manager = GetManager();
  HandleOf<Physics2dMaterial> cloneHandle(manager->CreateRuntimeInternal());
  Physics2dMaterial* clone = *cloneHandle;
  CopyTo(clone);
  return cloneHandle;
}

float Physics2dMaterial::GetFriction()
{
  return mDynamicFriction;
}

void Physics2dMaterial::SetFriction(float friction)
{
  if(friction < float(0))
  {
    friction = float(0);
    Zero::DoNotifyWarning("Invalid friction bounds.", "Friction cannot be negative.");
  }
  if(friction > float(1000000))
  {
    friction = float(1000000);
    Zero::DoNotifyWarning("Invalid friction bounds.", "Friction is too large");
  }

  mDynamicFriction = mStaticFriction = friction;
}

float Physics2dMaterial::GetDensity()
{
  return mDensity;
}

void Physics2dMaterial::SetDensity(float density)
{
  SetDensityInternal(density);
}

void Physics2dMaterial::CopyTo(Physics2dMaterial* destination)
{
  destination->mRestitution = mRestitution;
  destination->mStaticFriction = mStaticFriction;
  destination->mDynamicFriction = mDynamicFriction;
  destination->mDensity = mDensity;
  destination->mRestitutionImportance = mRestitutionImportance;
  destination->mFrictionImportance = mFrictionImportance;
}

void Physics2dMaterial::UpdateAndNotifyIfModified()
{
  if(mModified == false)
    return;

  mModified = false;
  // If our values change then we need to let all collider's who are using this resource know
  // so they can re-compute any necessary values (currently only the density)
  Zero::ResourceEvent toSend;
  toSend.EventResource = this;
  DispatchEvent(Zero::Events::ResourceModified, &toSend);
}

void Physics2dMaterial::SetDensityInternal(float density, bool markModified)
{
  if(density == float(0))
    density = float(0);
  else if(density < float(.001f))
  {
    density = float(.001f);
    Zero::DoNotifyWarning("Too small of a density.", "The density being set is too small and "
      "will likely result in floating point inaccuracies. If you would like "
      "to make the object massless, please set the density to 0.");
  }
  else if(density > float(1e+9))
  {
    density = float(1e+9);
    Zero::DoNotifyWarning("Too large of a density.", "The density being set is too large and "
      "will likely result in floating point inaccuracies.");
  }

  mDensity = density;
  if(markModified)
    ResourceModified();
}

}//namespace Physics2dCore
