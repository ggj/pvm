#include "main.h"
#include "assets.h"
#include "options.h"
#include "app.h"

Options::Options()
	: bFinished(FALSE)
	, iOption((u32)OptionControlType)
	, bWaitingFinish(FALSE)
	, fNextX(0.0f)
	, fNextY(0.0f)
	, fPrevX(0.0f)
	, fPrevY(0.0f)
{
	pInput->AddKeyboardListener(this);

	sptBg.Load(SPT_MENU);
	sptBg.SetPriority(1);
	pScene->Add(&sptBg);

	sptBase.Load(SPT_BASE);
	sptBase.SetPriority(1);
	sptBase.SetPosition(0.22363f, 0.4414f);
	pScene->Add(&sptBase);

	sptTitle.Load(SPT_OPTIONS_TITLE);
	sptTitle.SetPriority(1);
	sptTitle.SetPosition(0.41894f, 0.5026f);
	pScene->Add(&sptTitle);

	sptControl.Load(SPT_CONTROL);
	sptControl.SetPriority(1);
	sptControl.SetPosition(0.26171f, 0.57161f);
	pScene->Add(&sptControl);

	sptControlType.Load(SPT_CONTROL_OPTION);
	sptControlType.SetPriority(1);
	sptControlType.SetPosition(0.55273f, 0.57812f);
	pScene->Add(&sptControlType);

	sptBgm.Load(SPT_BGM);
	sptBgm.SetPriority(1);
	sptBgm.SetPosition(0.26171f, 0.64322f);
	pScene->Add(&sptBgm);

	sptBgmVol.Load(SPT_VOLUME);
	sptBgmVol.SetPriority(1);
	sptBgmVol.SetPosition(0.54101f, 0.64583f);
	pScene->Add(&sptBgmVol);

	sptSfx.Load(SPT_SFX);
	sptSfx.SetPriority(1);
	sptSfx.SetPosition(0.26171f, 0.71223f);
	pScene->Add(&sptSfx);

	sptSfxVol.Load(SPT_VOLUME);
	sptSfxVol.SetPriority(1);
	sptSfxVol.SetPosition(0.54101f, 0.71484f);
	pScene->Add(&sptSfxVol);

	sptFullscreen.Load(SPT_FULLSCREEN);
	sptFullscreen.SetPriority(1);
	sptFullscreen.SetPosition(0.26171f, 0.78125f);
	pScene->Add(&sptFullscreen);

	sptFullscreenCheck.Load(SPT_CHECKBOX);
	sptFullscreenCheck.SetPriority(1);
	sptFullscreenCheck.SetPosition(0.52343f, 0.79557f);
	pScene->Add(&sptFullscreenCheck);

	sptExit.Load(SPT_EXIT);
	sptExit.SetPriority(1);
	sptExit.SetPosition(0.26171f, 0.85156f);
	pScene->Add(&sptExit);

	sptNext.Load(SPT_NEXT);
	sptNext.SetPriority(1);
	sptNext.SetPosition(0.0f, 0.0f);
	pScene->Add(&sptNext);

	sptPrev.Load(SPT_PREV);
	sptPrev.SetPriority(1);
	sptPrev.SetPosition(0.0f, 0.0f);
	pScene->Add(&sptPrev);

	sfxChange.Load(SFX_POWERUP_01);
	pSoundSystem->Add(&sfxChange);

	sfxOk.Load(SFX_POWERUP_03);
	pSoundSystem->Add(&sfxOk);

	this->UpdateAnimation();
}

Options::~Options()
{
	pScene->Reset();
	pInput->RemoveKeyboardListener(this);
}

void Options::Update(f32 dt)
{
	if (bWaitingFinish)// && !sfxOk.IsPlaying())
	{
		u32 type = sptControlType.GetAnimation();
		pApp->SetControlType((eControlType)type);

		bFinished = TRUE;
	}
}

void Options::UpdateAnimation()
{
	sptControl.SetAnimation(0u);
	sptBgm.SetAnimation(0u);
	sptSfx.SetAnimation(0u);
	sptFullscreen.SetAnimation(0u);
	sptExit.SetAnimation(0u);

	sptNext.SetVisible(TRUE);
	sptPrev.SetVisible(TRUE);

	sptBgmVol.SetCurrentFrame(static_cast<u32>(pSoundSystem->GetMusicVolume() * (sptBgmVol.GetNumFrames() - 1)));
	sptSfxVol.SetCurrentFrame(static_cast<u32>(pSoundSystem->GetSfxVolume() * (sptSfxVol.GetNumFrames() - 1)));

	switch ((eOptionConfig)iOption)
	{
		case OptionControlType:
		default:
		{
			sptControl.SetAnimation(1u);
			fPrevX = 0.51562f;
			fPrevY = 0.58854f;
			fNextX = 0.70117f;
			fNextY = 0.58854f;

			if (pInput->GetMaximumJoysticks() == 0)
			{
				sptNext.SetVisible(FALSE);
				sptPrev.SetVisible(FALSE);
			}
		}
		break;

		case OptionBgmVolume:
		{
			sptBgm.SetAnimation(1u);
			fPrevX = 0.51562f;
			fPrevY = 0.66145f;
			fNextX = 0.625f;
			fNextY = 0.66145f;
		}
		break;

		case OptionSfxVolume:
		{
			sptSfx.SetAnimation(1u);
			fPrevX = 0.51562f;
			fPrevY = 0.73177f;
			fNextX = 0.625f;
			fNextY = 0.73177f;
		}
		break;

		case OptionFullscreen:
		{
			sptFullscreen.SetAnimation(1u);
			sptNext.SetVisible(FALSE);
			sptPrev.SetVisible(FALSE);
		}
		break;

		case OptionExit:
		{
			sptExit.SetAnimation(1u);
			sptNext.SetVisible(FALSE);
			sptPrev.SetVisible(FALSE);
		}
		break;
	}

	if (pScreen->IsFullscreen())
	{
		sptFullscreenCheck.SetAnimation("selected");
	}
	else
	{
		sptFullscreenCheck.SetAnimation("normal");
	}

	sptNext.SetPosition(fNextX, fNextY);
	sptPrev.SetPosition(fPrevX, fPrevY);
}

void Options::OnInputKeyboardPress(const EventInputKeyboard *ev)
{
	if (bWaitingFinish)
		return;

	Key k = ev->GetKey();

	switch (k.GetValue())
	{
		case Seed::KeyLeft:
		{
			sptPrev.SetAnimation(1u);
			sptNext.SetAnimation(0u);

			switch ((eOptionConfig)iOption)
			{
				case OptionControlType:
				{
					u32 joy = pInput->GetMaximumJoysticks();

					u32 end = 2;
					if (joy == 2)
						end = 1;

					if (joy)
					{
						if (sptControlType.GetAnimation() > 0)
							sptControlType.SetAnimation(sptControlType.GetAnimation() - 1);
						else
							sptControlType.SetAnimation(sptControlType.GetNumAnimations() - end);
					}
				}
				break;

				case OptionBgmVolume:
				{
					if (sptBgmVol.GetCurrentFrame() > 0)
						pSoundSystem->SetMusicVolume(pSoundSystem->GetMusicVolume() - 0.15f);
					else
						pSoundSystem->SetMusicVolume(0.0f);
				}
				break;

				case OptionSfxVolume:
				{
					if (sptSfxVol.GetCurrentFrame() > 0)
						pSoundSystem->SetSfxVolume(pSoundSystem->GetSfxVolume() - 0.15f);
					else
						pSoundSystem->SetSfxVolume(0.0f);
				}
				break;

				default:
				break;
			}

			sfxChange.Play();
			this->UpdateAnimation();
		}
		break;

		case Seed::KeyRight:
		{
			sptPrev.SetAnimation(0u);
			sptNext.SetAnimation(1u);

			switch ((eOptionConfig)iOption)
			{
				case OptionControlType:
				{
					u32 joy = pInput->GetMaximumJoysticks();

					u32 end = 2;
					if (joy == 2)
						end = 1;

					if (joy)
					{
						if (sptControlType.GetAnimation() < sptControlType.GetNumAnimations() - end)
							sptControlType.SetAnimation(sptControlType.GetAnimation() + 1);
						else
							sptControlType.SetAnimation(0u);
					}
				}
				break;

				case OptionBgmVolume:
				{
					if (sptBgmVol.GetCurrentFrame() < sptBgmVol.GetNumFrames() - 1)
						pSoundSystem->SetMusicVolume(pSoundSystem->GetMusicVolume() + 0.15f);
				}
				break;

				case OptionSfxVolume:
				{
					if (sptSfxVol.GetCurrentFrame() < sptSfxVol.GetNumFrames() - 1)
						pSoundSystem->SetSfxVolume(pSoundSystem->GetSfxVolume() + 0.15f);
				}
				break;

				default:
				break;
			}

			sfxChange.Play();
			this->UpdateAnimation();
		}
		break;

		case Seed::KeyUp:
		{
			iOption--;
			if (iOption < (s32)OptionConfigStart)
				iOption = OptionConfigEnd;

			sfxChange.Play();
			this->UpdateAnimation();
		}
		break;

		case Seed::KeyDown:
		{
			iOption++;
			if (iOption > (s32)OptionConfigEnd)
				iOption = OptionConfigStart;

			sfxChange.Play();
			this->UpdateAnimation();
		}
		break;

		case Seed::KeyReturn:
		{
			if (iOption == OptionExit)
			{
				sfxOk.Play();
				bWaitingFinish = TRUE;
			}
			else if (iOption == OptionFullscreen)
			{
				pScreen->ToggleFullscreen();
				this->UpdateAnimation();
			}
		}
		break;

		default:
		break;
	}
}


void Options::OnInputKeyboardRelease(const EventInputKeyboard *ev)
{
	if (bWaitingFinish)
		return;

	Key k = ev->GetKey();

	switch (k.GetValue())
	{
		case Seed::KeyLeft:
		{
			sptPrev.SetAnimation(0u);
			sptNext.SetAnimation(0u);
		}
		break;

		case Seed::KeyRight:
		{
			sptPrev.SetAnimation(0u);
			sptNext.SetAnimation(0u);
		}
		break;

		default:
		break;
	}
}

BOOL Options::IsFinished() const
{
	return bFinished;
}
