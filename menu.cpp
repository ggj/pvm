#include "menu.h"
#include "app.h"
#include "assets.h"

#define BTN_PLAY 1
#define BTN_OPTIONS 2
#define BTN_CREDITS 3
#define BTN_QUIT 4

Menu::Menu()
{
	iSelected = (u32)OptionPlay;
	bFinished = FALSE;
	bWaitingFinish = FALSE;
	fAnimPosY = 0.55989f;

	pInput->AddKeyboardListener(this);

	sptBg.Load(SPT_MENU);
	pScene->Add(&sptBg);

	sptStart.Load(SPT_PLAY);
	sptStart.SetPosition(0.33203f, 0.52343f);
	sptStart.SetPriority(1);
	pScene->Add(&sptStart);

	sptCredits.Load(SPT_CREDITS);
	sptCredits.SetPosition(0.33203f, 0.75781f);
	sptCredits.SetPriority(1);
	pScene->Add(&sptCredits);

	sptOptions.Load(SPT_OPTIONS);
	sptOptions.SetPosition(0.33203f, 0.65104f);
	sptOptions.SetPriority(1);
	pScene->Add(&sptOptions);

	sptQuit.Load(SPT_QUIT);
	sptQuit.SetPosition(0.33203f, 0.86458f);
	sptQuit.SetPriority(1);
	pScene->Add(&sptQuit);

	btnStart.Initialize(BTN_PLAY);
	btnStart.SetSprite(SPT_PLAY);
	btnStart.SetPosition(0.33203f, 0.52343f);
	btnStart.SetPriority(1);
	btnStart.AddListener(this);
	pGuiManager->Add(&btnStart);

	btnCredits.Initialize(BTN_CREDITS);
	btnCredits.SetSprite(SPT_CREDITS);
	btnCredits.SetPosition(0.33203f, 0.75781f);
	btnCredits.SetPriority(1);
	btnCredits.AddListener(this);
	pGuiManager->Add(&btnCredits);

	btnOptions.Initialize(BTN_OPTIONS);
	btnOptions.SetSprite(SPT_OPTIONS);
	btnOptions.SetPosition(0.33203f, 0.65104f);
	btnOptions.SetPriority(1);
	btnOptions.AddListener(this);
	pGuiManager->Add(&btnOptions);

	btnQuit.Initialize(BTN_QUIT);
	btnQuit.SetSprite(SPT_QUIT);
	btnQuit.SetPosition(0.33203f, 0.86458f);
	btnQuit.SetPriority(1);
	btnQuit.AddListener(this);
	pGuiManager->Add(&btnQuit);

	sptPanda.Load(SPT_PANDA);
	sptPanda.SetPriority(1);
	sptPanda.SetAnimation("run");
	sptPanda.SetScale(-1.0f, 1.0f);
	pScene->Add(&sptPanda);

	sptMaya.Load(SPT_MAIA);
	sptMaya.SetPriority(1);
	sptMaya.SetAnimation("run");
	sptMaya.SetScale(-1.0f, 1.0f);
	pScene->Add(&sptMaya);

	sfxChange.Load(SFX_POWERUP_01);
	//sfxChange.SetVolume(0.1f);
	pSoundSystem->Add(&sfxChange);

	sfxOk.Load(SFX_POWERUP_03);
	//sfxOk.SetVolume(0.1f);
	pSoundSystem->Add(&sfxOk);

	this->UpdateAnimation();
}

Menu::~Menu()
{
	pScene->Reset();
	pInput->RemoveKeyboardListener(this);
	pResourceManager->GarbageCollect();
}

void Menu::Update(f32 dt)
{
	if (bWaitingFinish)// && !sfxOk.IsPlaying())
	{
		bFinished = TRUE;
	}
}

void Menu::UpdateAnimation()
{
	sptStart.SetAnimation(0u);
	sptCredits.SetAnimation(0u);
	sptOptions.SetAnimation(0u);
	sptQuit.SetAnimation(0u);

	switch ((eMenuOption)iSelected)
	{
		case OptionPlay:
		default:
		{
			sptStart.SetAnimation(1u);
			fAnimPosY = 0.55989f;
		}
		break;

		case OptionOptions:
		{
			sptOptions.SetAnimation(1u);
			fAnimPosY = 0.67057f;
		}
		break;

		case OptionCredits:
		{
			sptCredits.SetAnimation(1u);
			fAnimPosY = 0.78125f;
		}
		break;

		case OptionQuit:
		{
			sptQuit.SetAnimation(1u);
			fAnimPosY = 0.88541f;
		}
		break;
	}

	sptMaya.SetPosition(0.62988f, fAnimPosY);
	sptPanda.SetPosition(0.30273f, fAnimPosY);
}

void Menu::OnInputKeyboardPress(const EventInputKeyboard *ev)
{
	if (bWaitingFinish)
		return;

	Key k = ev->GetKey();

	switch (k.GetValue())
	{
		case Seed::KeyUp:
		{
			iSelected--;
			if (iSelected < (s32)OptionsStart)
				iSelected = (s32)OptionsEnd;

			sfxChange.Play();
			this->UpdateAnimation();
		}
		break;

		case Seed::KeyDown:
		{
			iSelected++;
			if (iSelected > (s32)OptionsEnd)
				iSelected = (s32)OptionsStart;

			sfxChange.Play();
			this->UpdateAnimation();
		}
		break;

		case Seed::KeyReturn:
		{
			sfxOk.Play();
			bWaitingFinish = TRUE;
		}
		break;

		default:
		break;
	}
}

void Menu::OnWidgetRollOver(const EventWidget *ev)
{
	if (bWaitingFinish)
		return;

	switch (ev->GetSender()->GetId())
	{
		case BTN_PLAY:
		{
			iSelected = OptionPlay;
		}
		break;

		case BTN_CREDITS:
		{
			iSelected = OptionCredits;
		}
		break;

		case BTN_OPTIONS:
		{
			iSelected = OptionOptions;
		}
		break;

		case BTN_QUIT:
		{
			iSelected = OptionQuit;
		}
		break;
	}

	this->UpdateAnimation();
}

void Menu::OnWidgetRelease(const EventWidget *ev)
{
	if (bWaitingFinish)
		return;

	switch (ev->GetSender()->GetId())
	{
		case BTN_PLAY:
		{
			iSelected = OptionPlay;
			sfxOk.Play();
			bWaitingFinish = TRUE;
		}
		break;

		case BTN_CREDITS:
		{
			iSelected = OptionCredits;
			sfxOk.Play();
			bWaitingFinish = TRUE;
		}
		break;

		case BTN_OPTIONS:
		{
			iSelected = OptionOptions;
			sfxOk.Play();
			bWaitingFinish = TRUE;
		}
		break;

		case BTN_QUIT:
		{
			iSelected = OptionQuit;
			sfxOk.Play();
			bWaitingFinish = TRUE;
		}
		break;
	}
}

eMenuOption Menu::GetOption() const
{
	return (eMenuOption)iSelected;
}

BOOL Menu::IsFinished() const
{
	return bFinished;
}
