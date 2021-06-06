#include "Precompiled.hpp"

#include "Physics2dMaterialManager.hpp"

namespace Physics2dCore
{

//---------------------------------------------------------- Physics2dMaterialManager
ImplementResourceManager(Physics2dMaterialManager, Physics2dMaterial);

Physics2dMaterialManager::Physics2dMaterialManager(BoundType* resourceType) : ResourceManager(resourceType)
{
  AddLoader("Physics2dMaterial", new Zero::TextDataFileLoader<Physics2dMaterialManager>());
  mCategory = "Physics";
  mCanAddFile = true;
  mOpenFileFilters.PushBack(Zero::FileDialogFilter("*.Physics2dMaterial.data"));
  DefaultResourceName = "DefaultPhysics2dMaterial";
  mCanCreateNew = true;
  mCanDuplicate = true;
  mExtension = Zero::DataResourceExtension;
}

void Physics2dMaterialManager::UpdateAndNotifyModifiedResources()
{
  for(size_t i = 0; i < mModifiedResources.Size(); ++i)
  {
    Physics2dMaterial* material = mModifiedResources[i];
    if(material != nullptr)
      material->UpdateAndNotifyIfModified();
  }
  mModifiedResources.Clear();
}

}//namespace Physics2dCore
