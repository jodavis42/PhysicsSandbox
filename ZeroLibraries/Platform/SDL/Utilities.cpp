///////////////////////////////////////////////////////////////////////////////
///
/// \file Utilities.cpp
/// Implementation of the Utilities class.
/// 
/// Authors: Trevor Sundberg
/// Copyright 2011, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Zero
{

namespace Os
{

void Sleep(uint ms)
{
  SDL_Delay((Uint32)ms);
}

#if !defined(ZeroPlatformNoIncompleteImplementations)
void SetTimerFrequency(uint ms)
{
  // Not supported by SDL.
}
#endif

const char* GetEnvironmentList(const char* defaultValue, const char* names[], size_t length)
{
  for (size_t i = 0; i < length; ++i)
  {
    const char* name = names[i];
    const char* result = getenv(name);

    if (result != nullptr && strlen(result) != 0)
      return result;
  }

  return defaultValue;
}

#if !defined(ZeroPlatformNoIncompleteImplementations)
String UserName()
{
  // There is no portable way to get the user name
  const char* names[] = { "USER", "USERNAME", "LOGNAME", "COMPUTERNAME", "HOSTNAME" };
  return GetEnvironmentList("User", names, SDL_arraysize(names));
}
#endif

#if !defined(ZeroPlatformNoIncompleteImplementations)
String ComputerName()
{
  // There is no portable way to get the computer/host name
  const char* names[] = { "COMPUTERNAME", "HOSTNAME", "USER", "USERNAME", "LOGNAME" };
  return GetEnvironmentList("Computer", names, SDL_arraysize(names));
}
#endif

#if !defined(ZeroPlatformNoIncompleteImplementations)
bool IsDebuggerAttached()
{
  // SDL cannot detect whether a debugger is attached.
  return false;
}
#endif

ZeroShared void DebuggerOutput(const char* message)
{
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s", message);
}

#if !defined(ZeroPlatformNoIncompleteImplementations)
u64 GetMacAddress()
{
  // Not supported by SDL.
  return 0;
}
#endif

void DebugBreak()
{
  SDL_TriggerBreakpoint();
}

#if !defined(ZeroPlatformNoIncompleteImplementations)
void EnableMemoryLeakChecking(int breakOnAllocation)
{
  // Not supported by SDL.
}
#endif

DeclareEnum4(ReturnCode, Continue, DebugBreak, Terminate, Ignore);

bool ErrorProcessHandler(ErrorSignaler::ErrorData& errorData)
{
  // Stores the resulting quote removed message from below
  String message;
  String expression = errorData.Expression;
  expression = expression.Replace("\"", "'");

  // Check if no message was provided
  if (errorData.Message != nullptr)
  {
    message = errorData.Message;
    message = message.Replace("\"", "'");
  }
  else
  {
    message = "No message";
  }

  ZPrint("%s\n", message.c_str());

  Console::Print(Filter::ErrorFilter, message.c_str());

  // Show a message box instead
  message = BuildString(message, "\nWould you like to continue?");
  
  const SDL_MessageBoxButtonData buttons[] =
  {
    { 0,                                       ReturnCode::Continue,    "Continue"   },
    { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, ReturnCode::DebugBreak,  "DebugBreak" },
    { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, ReturnCode::Terminate,   "Terminate"  },
    { 0,                                       ReturnCode::Ignore,      "Ignore"     },
  };

  SDL_MessageBoxData data =
  {
    SDL_MESSAGEBOX_INFORMATION,
    nullptr,
    "Error",
    message.c_str(),
    SDL_arraysize(buttons),
    buttons,
    nullptr
  };

  int buttonId = -1;
  SDL_ShowMessageBox(&data, &buttonId);

  // Based on the exit code...
  switch (buttonId)
  {
  case ReturnCode::Continue:
    // No debug break, just continue
    return false;

  case ReturnCode::DebugBreak:
    // Returning true will cause a break point
    return true;

  case ReturnCode::Terminate:
    // Immediately kill the application
    abort();
    return false;

  case ReturnCode::Ignore:
    errorData.IgnoreFutureAssert = true;
    return false;

  default:
    // Force a break point, we have no idea what we got back
    return true;
  }
}

#if !defined(ZeroPlatformNoIncompleteImplementations)
void WebRequest(
  Status& status,
  StringParam url,
  const Array<WebPostData>& postDatas,
  const Array<String>& additionalRequestHeaders,
  WebRequestHeadersFn onHeadersReceived,
  WebRequestDataFn onDataReceived,
  void* userData)
{
  status.SetFailed("WebRequest not supported by SDL");
}
#endif

#if !defined(ZeroPlatformNoIncompleteImplementations)
bool SystemOpenFile(Status& status, cstr file, uint verb, cstr parameters, cstr workingDirectory)
{
  // Unfortunately we have no portable way of using the working directory.
  String commandLine = String::Format("\"%s\" %s", file, parameters);
  int result = system(commandLine.c_str());
  return result != 0;
}
#endif

#if !defined(ZeroPlatformNoIncompleteImplementations)
bool SystemOpenNetworkFile(Status& status, cstr file, uint verb, cstr parameters, cstr workingDirectory)
{
  return SystemOpenFile(status, file, verb, parameters, workingDirectory);
}
#endif

String GetEnvironmentalVariable(StringParam variable)
{
  return getenv(variable.c_str());
}

//---------------------------------------------------------------- Memory Status 
#if !defined(ZeroPlatformNoIncompleteImplementations)
void GetMemoryStatus(MemoryInfo& data)
{
  // Not supported by SDL.
  data.Commit = 0;
  data.Free = 0;
  data.Reserve = 0;
}
#endif

String GetVersionString()
{
  SDL_version version;
  SDL_GetVersion(&version);
  return String::Format("%s SDL %d.%d.%d", SDL_GetPlatform(), version.major, version.minor, version.patch);
}

}

u64 GenerateUniqueId64()
{
  if (gDeterministicMode)
  {
    static u64 deterministicId = 0;
    ++deterministicId;
    return deterministicId;
  }

  u64 result = SDL_GetPerformanceCounter() ^ SDL_GetTicks();

  static u64 highCount = 0;
  ++highCount;
  result += (highCount << 48) ^ Os::UserName().Hash();

  return result;
}
}
