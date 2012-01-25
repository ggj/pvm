#include "app.h"

ISceneNode *pScene;
ISceneNode *pSceneStatic;
App *pApp;

#if defined(_IPHONE_)
ePlatformType nPlatform = TouchDevice;
#elif defined(_WII_)
ePlatformType nPlatform = GameConsole;
#else
ePlatformType nPlatform = PersonalComputer;
#endif


void seed_main(int argc, char **argv)
{
	App app;
	pApp = &app;

	Seed::SetGameApp(&app, argc, argv);
	if (Seed::Initialize())
	{
		if (argv[1] && STRCASECMP(argv[1], "--fullscreen") == 0)
			pScreen->ToggleFullscreen();

		while (!pSystem->IsShuttingDown())
		{
			if (!app.HasError())
			{
				Seed::Update();
			}
			pTimer->Sleep(1);
		}
	}
	Seed::Shutdown();
}

#ifdef APPUP_STORE
#include "adpcore.h"

#if DEBUG
	#define INTEL_APPUP_GUID ADP_DEBUG_APPLICATIONID
	//#define INTEL_APPUP_GUID ADP_EXPIRED_APPLICATIONID
#else
	ADP_APPLICATIONID appId;
	#define INTEL_APPUP_GUID appId
#endif

int main(int argc, char **argv)
{
#ifndef DEBUG
	appId.field[0] = 0x6FBFE8F7;
	appId.field[1] = 0x18B04D4C;
	appId.field[2] = 0xB2E3CF44;
	appId.field[3] = 0xBC6AA937;
#endif

	ADP_RET_CODE ret = ADP_Initialize();
	ret = ADP_IsAuthorized(INTEL_APPUP_GUID);
	if (ret == ADP_AUTHORIZED)
	{
		ret = ADP_ApplicationBeginEvent();
		seed_main(argc, argv);
		ret = ADP_ApplicationEndEvent();
	}
	else
	{
		MessageBox(0, L"Something is wrong with your installation.", L"Error", 0);
	}

	ret = ADP_Close();

	return EXIT_SUCCESS;
}
#elif !defined(_IPHONE_)
int main(int argc, char **argv)
{
	seed_main(argc, argv);
	return EXIT_SUCCESS;
}
#endif
