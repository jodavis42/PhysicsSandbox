#include "Precompiled.hpp"

#include "Physics2dLibraryTCS.hpp"

#include "Components/PhysicsSpace2dTCS.hpp"
#include "Components/RigidBody2dTCS.hpp"
#include "Components/Collider2dTCS.hpp"

namespace Zero
{

using namespace Physics2dTCS;

//-------------------------------------------------------------------Physics2dLibraryTCS
ZilchDefineStaticLibrary(Physics2dLibraryTCS)
{
  builder.CreatableInScriptDefault = false;

  // Resources

  // Components
  ZilchInitializeType(PhysicsSpace2dTCS);
  ZilchInitializeType(RigidBody2dTCS);
  ZilchInitializeType(Collider2dTCS);

  EngineLibraryExtensions::AddNativeExtensions(builder);
}

void Physics2dLibraryTCS::Initialize()
{
  BuildStaticLibrary();
  MetaDatabase::GetInstance()->AddNativeLibrary(GetLibrary());
}

void Physics2dLibraryTCS::Shutdown()
{
  GetLibrary()->ClearComponents();
}

}//namespace Zero
