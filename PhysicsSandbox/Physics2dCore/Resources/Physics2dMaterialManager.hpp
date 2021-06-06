#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

#include "Physics2dCore/Resources/Physics2dMaterial.hpp"

namespace Physics2dCore
{

//----------------------------------------------------------Physics2dMaterialManager
class Physics2dMaterialManager : public Zero::ResourceManager
{
public:
  DeclareResourceManager(Physics2dMaterialManager, Physics2dMaterial);
  Physics2dMaterialManager(BoundType* resourceType);

  void UpdateAndNotifyModifiedResources();

  using Physics2dMaterialReference = HandleOf<Physics2dMaterial> ;
  Array<Physics2dMaterialReference> mModifiedResources;
};

}//namespace Physics2dCore
