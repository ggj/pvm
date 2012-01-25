#include "app.h"
#include "assets.h"
#include "menu.h"
#include "game.h"
#include "credits.h"
#include "tutorial.h"
#include "thanks.h"
#include "options.h"
#include "intro.h"

App::App()
	: eState(INTRO)
	, pIntro(NULL)
	, pMenu(NULL)
	, pGame(NULL)
	, pOptions(NULL)
	, pCredits(NULL)
	, pTutorial(NULL)
	, pThanks(NULL)
	, nControlType(Keyboard1Keyboard2)
{
	cConfig.SetRendererDeviceType(Seed::RendererDeviceOpenGL14);
	//cConfig.SetVideoMode(Seed::Video_iPhonePortrait);
	cConfig.SetVideoMode(Seed::Video_1024x768);
	//cConfig.SetVideoMode(Seed::Video_Netbook);
	cConfig.SetFrameRate(Seed::FrameRateLockAt30);
	//cConfig.SetPlatformSimulation(Seed::SimulateIOS3G);
	//cConfig.bDebugSprite = TRUE;
	cConfig.SetApplicationTitle("Pandas vs. Mayas!");
	cConfig.SetApplicationDescription("Pandas vs. Mayas!");
}

App::~App()
{
	
}

BOOL App::Initialize()
{
	IGameApp::Initialize();

	pSystem->AddListener(this);
	pInput->AddKeyboardListener(this);

	/* ------- Rendering Initialization ------- */
	cScene.SetPriority(0);
	cSceneStatic.SetPriority(PRIORITY_CURSOR);

	cRenderer.Add(&cScene);
	cRenderer.Add(&cSceneStatic);

	cViewport.SetRenderer(&cRenderer);
	pViewManager->Add(&cViewport);
	pRendererManager->Add(&cRenderer);

	pSceneManager->Add(&cScene);
	pSceneManager->Add(&cSceneStatic);

	pScene = &cScene;
	pSceneStatic = &cSceneStatic;

	musTheme.Load(BGM_MUSIC);
	//musTheme.SetVolume(0.05f);
	musTheme.SetAutoUnload(TRUE);
	pSoundSystem->PlayMusic(&musTheme, 500);

	pRand->Initialize(clock());

	this->OnEnterState();
	/* ------- Rendering Initialization ------- */

	return TRUE;
}

void App::Destroy()
{
	if (pIntro)
		Delete(pIntro);

	if (pMenu)
		Delete(pMenu);

	if (pGame)
		Delete(pGame);

	if (pCredits)
		Delete(pCredits);

	if (pTutorial)
		Delete(pTutorial);

	if (pThanks)
		Delete(pThanks);

	if (pOptions)
		Delete(pOptions);
}

void App::Quit()
{
	this->Destroy();
	pSystem->Shutdown();
}

BOOL App::Shutdown()
{
	pSoundSystem->StopMusic();
	musTheme.Unload();

	this->Destroy();

	pInput->RemoveKeyboardListener(this);
	pSystem->RemoveListener(this);

	return IGameApp::Shutdown();
}

BOOL App::Reset()
{
	return TRUE;
}

BOOL App::HasError() const
{
	return FALSE;
}

void App::OnSystemShutdown(const EventSystem *ev)
{
	this->Destroy();
	pSystem->Shutdown();
}

void App::OnInputKeyboardRelease(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	switch (k.GetValue())
	{
		case Seed::KeyEscape:
		{
/*			if (eState != THANKS)
			{
				this->OnLeaveState();
				eState = THANKS;
				this->OnEnterState();
			}*/
			this->Quit();
		}
		break;

		default:
		break;
	}
}

BOOL App::Update(f32 dt)
{
	switch (eState)
	{
		case INTRO:
		{
			pIntro->Update(dt);
			if (pIntro->IsFinished())
			{
				this->OnLeaveState();
				eState = MENU;
				this->OnEnterState();
			}
		}
		break;

		case MENU:
		{
			pMenu->Update(dt);
			if (pMenu->IsFinished())
			{
				eMenuOption opt = pMenu->GetOption();
				this->OnLeaveState();

				switch (opt)
				{
					case OptionPlay:
						eState = TUTORIAL;
					break;

					case OptionOptions:
						eState = OPTIONS;
					break;

					case OptionCredits:
						eState = CREDITS;
					break;

					case OptionQuit:
						//eState = THANKS;
						this->Quit();
					break;
				}

				this->OnEnterState();
			}
		}
		break;

		case GAME:
		{
			pGame->Update(dt);
			if (pGame->IsFinished())
			{
				this->OnLeaveState();
				eState = MENU;
				this->OnEnterState();
			}
		}
		break;

		case OPTIONS:
		{
			pOptions->Update(dt);
			if (pOptions->IsFinished())
			{
				this->OnLeaveState();
				eState = MENU;
				this->OnEnterState();
			}
		}
		break;

		case CREDITS:
		{
			pCredits->Update(dt);
			if (pCredits->IsFinished())
			{
				this->OnLeaveState();
				eState = THANKS;
				this->OnEnterState();
			}
		}
		break;

		case TUTORIAL:
		{
			pTutorial->Update(dt);
			if (pTutorial->IsFinished())
			{
				this->OnLeaveState();
				eState = GAME;
				this->OnEnterState();
			}
		}
		break;

		case THANKS:
		{
			pThanks->Update(dt);
			if (pThanks->IsFinished())
			{
				//this->Destroy();
				this->OnLeaveState();
				//pSystem->Shutdown();
				eState = MENU;
				this->OnEnterState();
			}
		}
		break;

		case EXIT:
		break;

		default:
		break;
	}

	return TRUE;
}

void App::OnEnterState()
{
	switch (eState)
	{
		case INTRO:
		{
			pIntro = New(Intro());
		}
		break;

		case MENU:
		{
			pMenu = New(Menu());
		}
		break;

		case GAME:
		{
			pGame = New(Game());
		}
		break;

		case OPTIONS:
		{
			pOptions = New(Options());
		}
		break;

		case CREDITS:
		{
			pCredits = New(Credits());
		}
		break;

		case TUTORIAL:
		{
			pTutorial = New(Tutorial());
		}
		break;

		case THANKS:
		{
			pThanks = New(Thanks());
		}
		break;

		case EXIT:
		break;

		default:
		break;
	}
}

void App::OnLeaveState()
{
	switch (eState)
	{
		case INTRO:
		{
			Delete(pIntro);
			pIntro = NULL;
		}
		break;

		case MENU:
		{
			Delete(pMenu);
			pMenu = NULL;
		}
		break;

		case GAME:
		{
			Delete(pGame);
			pGame = NULL;
		}
		break;

		case OPTIONS:
		{
			Delete(pOptions);
			pOptions = NULL;
		}
		break;

		case CREDITS:
		{
			Delete(pCredits);
			pCredits = NULL;
		}
		break;

		case TUTORIAL:
		{
			Delete(pTutorial);
			pTutorial = NULL;
		}
		break;

		case THANKS:
		{
			Delete(pThanks);
			pThanks = NULL;
		}
		break;

		case EXIT:
		break;

		default:
		break;
	}
}

void App::SetControlType(eControlType type)
{
	nControlType = type;
}

eControlType App::GetControlType() const
{
	return nControlType;
}
