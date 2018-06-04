///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Josh Davis
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Zero
{

//Application Startup Function
bool ZeroLauncherStartup(Engine* engine, StringMap& parameters, StringParam dllPath);

}//namespace Zero

using namespace Zero;

extern "C" ZeroShared int RunZeroLauncher(const char* dllPath)
{
  //Set the log and error handlers so debug printing
  //and asserts will print to the Visual Studio Output Window.
  DebuggerListener debuggerOutput;
  if(Os::IsDebuggerAttached())
    Zero::Console::Add(&debuggerOutput);
  
  //Mirror console output to a log file
  FileListener fileListener;
  // Change the base log file's name
  fileListener.mBaseLogFileName = "ZeroLauncherLog_";
  Zero::Console::Add(&fileListener);

  //Used custom dialog box
  ErrorSignaler::SetErrorHandler(Os::ErrorProcessHandler);

  //Enable the crash handler
  CrashHandler::Enable();
  CrashHandler::AppendToExtraSymbolPath(dllPath);

  CrashHandler::SetPreMemoryDumpCallback(Zero::LauncherCrashPreMemoryDumpCallback, NULL);
  CrashHandler::SetCustomMemoryCallback(Zero::LauncherCrashCustomMemoryCallback, NULL);
  CrashHandler::SetLoggingCallback(Zero::LauncherCrashLoggingCallback, &fileListener);
  CrashHandler::SetSendCrashReportCallback(Zero::LauncherSendCrashReport, NULL);
  CrashHandler::SetCrashStartCallback(Zero::LauncherCrashStartCallback, NULL);

  ZPrint("Loading ZeroLauncher %d.0.\n", GetLauncherMajorVersion());

  // Initialize platform socket library
  Zero::Status socketLibraryInitStatus;
  Zero::Socket::InitializeSocketLibrary(socketLibraryInitStatus);
  Assert(Zero::Socket::IsSocketLibraryInitialized());

  // For some reason, old launcher exes will have a giant hang on load with newer dlls
  // unless a webrequest successfully runs first. No idea why this happens but this at
  // least fixes it for now...
  {
    String majorVersionIdStr = ToString(GetLauncherMajorVersion());
    String url = BuildString("https://builds.zeroengine.io?Commands=CheckPatchId&MajorId=", majorVersionIdStr);
    BlockingWebRequest request;
    request.mUrl = url;
    request.mSendEvent = false;
    String serverDllDate = request.Run();
  }

  Environment* environment = Environment::GetInstance();
  environment->ParseCommandArgs(gCommandLineArguments);

  // Startup the engine
  ZeroLauncherStartupSettings settings;
  settings.mTweakableFileName = "LauncherTweakables";
  settings.mEmbeddedPackage = false;
  settings.mDllPath = dllPath;

  // Startup the engine
  Zero::LauncherStartup startup;
  Engine* engine = startup.Initialize(settings);

  // Check and see if another launcher is already open (has to happen after startup)
  Status status;
  String mutexId = BuildString("ZeroLauncherMutex:{", GetLauncherGuidString(), "}");
  InterprocessMutex mutex;
  mutex.Initialize(status, mutexId.c_str(), true);
  if(status.Failed())
  {
    ZPrint("Mutex is already open. Sending a message to the open launcher and closing\n");
    Zero::LauncherSingletonCommunication communicator(environment->mParsedCommandLineArguments);
    return 0;
  }

  CrashHandler::SetRestartCommandLine(environment->mCommandLine);
  
  //Run application startup
  bool success = Zero::ZeroLauncherStartup(engine, environment->mParsedCommandLineArguments, String(dllPath));
  //Failed startup do not run
  if(!success)
    return 0;

  // Return code of 0 means don't restart the launcher
  int returnCode = 0;
  //Run engine until termination
  engine->Run(false);

  // Check to see if we need to restart after we close (in order to update)
  // and if so change the return code to tell the exe.
  Cog* configCog = engine->GetConfigCog();
  LauncherConfig* config = configCog->has(LauncherConfig);
  if(config->mRestartOnClose)
    returnCode = 1;

  engine->Shutdown();
  // Free the launcher
  SafeDelete(Z::gLauncher);

  startup.Shutdown();
  // Uninitialize platform socket library
  Zero::Status socketLibraryUninitStatus;
  Zero::Socket::UninitializeSocketLibrary(socketLibraryUninitStatus);
  
  //Assert(!Zero::Socket::IsSocketLibraryInitialized());
  
  ZPrint("Terminated\n");

  return returnCode;
}