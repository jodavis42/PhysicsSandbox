#pragma once

#include "Physics2dCoreStandard.hpp"

namespace Zero
{

//-------------------------------------------------------------------Physics2dCoreLibrary
class ZeroNoImportExport Physics2dCoreLibrary : public Zilch::StaticLibrary
{
public:
  ZilchDeclareStaticLibraryInternals(Physics2dCoreLibrary, "ZeroEngine");

  static void Initialize();
  static void Shutdown();
};

}//namespace Zero

