///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Claeys
/// Copyright 2017, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "LibraryInitializer.hpp"

namespace Zero
{

//------------------------------------------------------------------------------------------ Startup
// Handles all platform agnostic initialization
class ZeroStartup
{
public:
  Engine* Initialize(ZeroStartupSettings& settings);
  void Shutdown();

protected:
  virtual void InitializeLibraries(ZeroStartupSettings& settings);
  Engine* InitializeEngine();
  ExecutableState* mState;
  ZilchSetup* mZilchSetup;
  Array<LibraryInitializer*> mLibararyInitializers;
};

}//namespace Zero
