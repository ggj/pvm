#include "main.h"
#include "assets.h"
#include "intro.h"

#define BTN_START 1

Intro::Intro()
	: bFinished(FALSE)
	, bWaitingFinish(FALSE)
	, bDir(FALSE)
	, fAlpha(1.0f)
{
	pInput->AddKeyboardListener(this);

	sptBg.Load(SPT_INTRO);
	sptBg.SetPriority(1);
	pScene->Add(&sptBg);

	btnStart.Initialize(BTN_START);
	btnStart.SetSprite(SPT_INTRO_START);
	btnStart.SetPriority(2);
	btnStart.SetPosition(0.39847f, 0.89713f);
	btnStart.AddListener(this);
	btnStart.SetSpriteBlending(Seed::BlendModulateAlpha);
	pScene->Add(&btnStart);
	pGuiManager->Add(&btnStart);

	sfxOk.Load(SFX_POWERUP_03);
	pSoundSystem->Add(&sfxOk);
}

Intro::~Intro()
{
	pGuiManager->Remove(&btnStart);
	pInput->RemoveKeyboardListener(this);
	pScene->Reset();
}

void Intro::Update(f32 dt)
{
	if (bWaitingFinish) // && !sfxOk.IsPlaying())
	{
		bFinished = TRUE;
	}

	if (bDir)
	{
		if (fAlpha < 1.0f)
		{
			fAlpha += dt;
		}
		else
		{
			fAlpha = 1.0f;
			bDir = FALSE;
		}
	}
	else
	{
		if (fAlpha > 0.0f)
		{
			fAlpha -= dt;
		}
		else
		{
			fAlpha = 0.0f;
			bDir = TRUE;
		}
	}

	btnStart.SetSpriteColor(1.0f, 1.0f, 1.0f, fAlpha);
}

void Intro::OnWidgetRelease(const EventWidget *ev)
{
	if (ev->GetSender()->GetId() == BTN_START)
	{
		sfxOk.Play();
		bWaitingFinish = TRUE;
	}
}

void Intro::OnInputKeyboardPress(const EventInputKeyboard *ev)
{
	if (bWaitingFinish)
		return;

	Key k = ev->GetKey();

	switch (k.GetValue())
	{
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

BOOL Intro::IsFinished() const
{
	return bFinished;
}
