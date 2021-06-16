#include "Precompiled.hpp"

#include "Physics2dCoreLibrary.hpp"

#include "Components/Colliders/Collider2d.hpp"
#include "Components/Colliders/BoxCollider2d.hpp"
#include "Components/Colliders/CircleCollider2d.hpp"
#include "Components/RigidBody2d.hpp"
#include "Events/ComponentCreatedEvent.hpp"
#include "Events/PropertyChangedEvent.hpp"
#include "Queries/Collider2dCastResult.hpp"
#include "Queries/Collider2dCastResults.hpp"
#include "Resources/Physics2dMaterial.hpp"
#include "Resources/Physics2dMaterialManager.hpp"
#include "SandboxGeometry/Shapes2d/Ray2d.hpp"

namespace Zero
{

using namespace Physics2dCore;

// Enums
ZilchDefineEnum(MassComputationMode);

ZilchDefineExternalBaseType(Ray2d, TypeCopyMode::ValueType, builder, type)
{
  type->CreatableInScript = true;
  ZilchBindDefaultCopyDestructor();
  ZilchFullBindConstructor(builder, type, ZilchSelf, "start, direction", Vec2Param, Vec2Param);

  ZilchBindMemberProperty(mStart);
  ZilchBindMemberProperty(mDirection);
  ZilchFullBindMethod(builder, type, &Ray::GetPoint, ZilchNoOverload, "GetPoint", "tValue")
    ->Description = ZilchDocumentString("Returns the point at the given t-value.");
  type->ToStringFunction = Zilch::BoundTypeToGlobalToString<Ray>;
  type->AddAttribute(ExportDocumentation);
}

//-------------------------------------------------------------------Physics2dCoreLibrary
ZilchDefineStaticLibrary(Physics2dCoreLibrary)
{
  builder.CreatableInScriptDefault = false;

  // Enums
  ZilchInitializeEnum(MassComputationMode);

  // Events
  ZilchInitializeType(ComponentCreatedEvent);
  ZilchInitializeType(PropertyChangedEvent);

  // Queries
  ZilchInitializeType(Collider2dCastResult);
  ZilchInitializeType(Collider2dCastResults);

  // Resources
  ZilchInitializeType(Physics2dMaterial);

  ZilchInitializeType(RigidBody2d);
  ZilchInitializeType(Collider2d);
  ZilchInitializeType(BoxCollider2d);
  ZilchInitializeType(CircleCollider2d);

  ZilchInitializeExternalType(Ray2d);

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
