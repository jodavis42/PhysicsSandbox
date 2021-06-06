#include "Precompiled.hpp"

#include "Physics2dCoreLibrary.hpp"

#include "Components/Colliders/Collider2d.hpp"
#include "Components/Colliders/BoxCollider2d.hpp"
#include "Components/Colliders/CircleCollider2d.hpp"
#include "Components/RigidBody2d.hpp"
#include "Events/ComponentCreatedEvent.hpp"
#include "Events/PropertyChangedEvent.hpp"
#include "Resources/Physics2dMaterial.hpp"
#include "Resources/Physics2dMaterialManager.hpp"

namespace Zero
{

using namespace Physics2dCore;

// Enums
ZilchDefineEnum(MassComputationMode);

//-------------------------------------------------------------------Physics2dCoreLibrary
ZilchDefineStaticLibrary(Physics2dCoreLibrary)
{
  builder.CreatableInScriptDefault = false;

  // Enums
  ZilchInitializeEnum(MassComputationMode);

  // Events
  ZilchInitializeType(ComponentCreatedEvent);
  ZilchInitializeType(PropertyChangedEvent);

  // Resources
  ZilchInitializeType(Physics2dMaterial);

  ZilchInitializeType(RigidBody2d);
  ZilchInitializeType(Collider2d);
  ZilchInitializeType(BoxCollider2d);
  ZilchInitializeType(CircleCollider2d);

  EngineLibraryExtensions::AddNativeExtensions(builder);
}

void Physics2dCoreLibrary::Initialize()
{
  BuildStaticLibrary();
  MetaDatabase::GetInstance()->AddNativeLibrary(GetLibrary());

  //Create the material manager.
  InitializeResourceManager(Physics2dMaterialManager);
}

void Physics2dCoreLibrary::Shutdown()
{
  GetLibrary()->ClearComponents();
}

}//namespace Zero
