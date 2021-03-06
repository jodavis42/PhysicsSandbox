///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2018, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Zero
{

//-------------------------------------------------------------------SpirVExtensionInstruction
SpirVExtensionInstruction::SpirVExtensionInstruction()
{
  mResolverFn = nullptr;
}

//-------------------------------------------------------------------SpirVExtensionLibrary
SpirVExtensionInstruction* SpirVExtensionLibrary::CreateExtInst(Zilch::Function* zilchFn, SpirVExtensionInstructionResolverFn resolverFn)
{
  ErrorIf(zilchFn == nullptr, "Invalid zilch function");
  ErrorIf(mExtensions.ContainsKey(zilchFn), "Extension already exists");

  SpirVExtensionInstruction* instruction = new SpirVExtensionInstruction();
  instruction->mResolverFn = resolverFn;
  instruction->mLibrary = this;
  mExtensions[zilchFn] = instruction;
  // Store this extension instruction in the owning library
  mOwningLibrary->mExtensionInstructions.InsertOrError(zilchFn, instruction);
  return instruction;
}

}//namespace Zero
