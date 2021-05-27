///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Claeys
/// Copyright 2017, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Zero
{

//------------------------------------------------------------------------------------------ LibraryInitializer
class LibraryInitializer
{
public:
  virtual void Intialize() abstract;
  virtual void Shutdown() abstract;
  virtual void ClearLibrary() abstract;
  virtual void Destroy() abstract;
};

//------------------------------------------------------------------------------------------ TypedLibraryInitializer
template <typename T>
class TypedLibraryInitializer : public LibraryInitializer
{
public:
  void Intialize() override
  {
    T::Initialize();
  }

  void Shutdown() override
  {
    T::Shutdown();
  }

  void ClearLibrary() override
  {
    T::GetInstance().ClearLibrary();
  }

  void Destroy() override
  {
    T::Destroy();
  }
};

}//namespace Zero
