#ifndef ExecutionMain_CPP_H__
#define ExecutionMain_CPP_H__

#include "../../../BaseProgramFile.h"

const char* ExecutionMain_CPP_FILE_NAME=R"(ExecutionMain.cpp)";
const char* ExecutionMain_CPP_PATH=R"(\\Source\\Private)";

const char* ExecutionMain_CPP_H=R"(
#include "ExecutionMain.h"

#include "RequiredProgramMainCPPInclude.h"
#include "Widgets/Testing/STestSuite.h"
#include "ISourceCodeAccessModule.h"
#include "Widgets/Testing/SPerfSuite.h"
#include "Widgets/Docking/SDockTab.h"
#include "SWebBrowser.h"
#include "Framework/Application/SlateApplication.h"
#include "IWebBrowserWindow.h"
#include "IWebBrowserPopupFeatures.h"
#include "ISlateReflectorModule.h"

IMPLEMENT_APPLICATION(ProgramTemplate, "ProgramTemplate");

#define LOCTEXT_NAMESPACE "ProgramTemplate"

namespace WorkspaceMenu
{
	TSharedRef<FWorkspaceItem> DeveloperMenu = FWorkspaceItem::NewGroup(LOCTEXT("DeveloperMenu", "Developer"));
}

int ExecutionMain(const TCHAR* pCmdLine)
{
    std::cout << "Program started!" << std::endl;

	// start up the main loop
	GEngineLoop.PreInit(GetCommandLineW());

	// Make sure all UObject classes are registered and default properties have been initialized
	ProcessNewlyLoadedUObjects();

	// Tell the module manager it may now process newly-loaded UObjects when new C++ modules are loaded
	FModuleManager::Get().StartProcessingNewlyLoadedObjects();

	// crank up a normal Slate application using the platform's standalone renderer	
	FSlateApplication::InitializeAsStandaloneApplication(GetStandardStandaloneRenderer());

	// Load the source code access module //////////// To be deleted ///////////
	ISourceCodeAccessModule& SourceCodeAccessModule = FModuleManager::LoadModuleChecked<ISourceCodeAccessModule>( FName( "SourceCodeAccess" ) );

	// create a test window
	FGlobalTabmanager::Get()->SetApplicationTitle(LOCTEXT("AppTitle", "ProgramTemplate"));
	TSharedPtr<SWindow> MainWindow = SNew(SWindow)
		.Title(LOCTEXT("MainWindow_Title", "Hello UE4!"))
		.ScreenPosition(FVector2D(800, 600))
		.ClientSize(FVector2D(900, 600))
		.AutoCenter(EAutoCenter::None);
		
	FSlateApplication::Get().AddWindow(MainWindow.ToSharedRef());

	// set the application name //////////// To be deleted ///////////
	FGlobalTabmanager::Get()->SetApplicationTitle(LOCTEXT("AppTitle", "Slate Viewer"));
	FModuleManager::LoadModuleChecked<ISlateReflectorModule>("SlateReflector").RegisterTabSpawner(WorkspaceMenu::DeveloperMenu);
	
	if (FParse::Param(FCommandLine::Get(), TEXT("perftest"))) //////////// To be deleted ///////////
	{
		// Bring up perf test
		SummonPerfTestSuite();
	}
	else
	{
		// Bring up the test suite.
		RestoreSlateTestSuite();
	}

	while (!GIsRequestingExit)
	{
		FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);
		FStats::AdvanceFrame(false);
		FTicker::GetCoreTicker().Tick(FApp::GetDeltaTime());
		FSlateApplication::Get().PumpMessages();
		FSlateApplication::Get().Tick();
		FPlatformProcess::Sleep(0);
	}
	
	FCoreDelegates::OnExit.Broadcast();
	FSlateApplication::Shutdown();
	FModuleManager::Get().UnloadModulesAtShutdown();

	return 0;
}
)";


class FileExecutionMain_cpp:public BaseProgramFile
{
public:
	virtual void Init(const std::string& pProgramName)override
	{
		BaseProgramFile::Init(pProgramName);
		
		file_name=ExecutionMain_CPP_FILE_NAME;
		file_path=ProgramName+ExecutionMain_CPP_PATH;
		file_content=ExecutionMain_CPP_H;
	}
};

FileExecutionMain_cpp ExecutionMain_cpp=FileExecutionMain_cpp();

#endif