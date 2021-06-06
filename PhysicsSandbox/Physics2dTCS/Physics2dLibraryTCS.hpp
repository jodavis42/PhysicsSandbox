#pragma once

#include "Physics2dStandardTCS.hpp"

namespace Zero
{

//-------------------------------------------------------------------Physics2dLibraryTCS
class ZeroNoImportExport Physics2dLibraryTCS : public Zilch::StaticLibrary
{
public:
  ZilchDeclareStaticLibraryInternals(Physics2dLibraryTCS, "ZeroEngine");

  static void Initialize();
  static void Shutdown();
};

}//namespace Zero

