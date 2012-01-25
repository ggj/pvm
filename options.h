#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include <Seed.h>
using namespace Seed;

enum eOptionConfig
{
	OptionConfigStart,
	OptionControlType = OptionConfigStart,
	OptionBgmVolume,
	OptionSfxVolume,
	OptionFullscreen,
	OptionExit,
	OptionConfigEnd = OptionExit,
};

class Options : public IEventInputKeyboardListener
{
	public:
		Options();
		virtual ~Options();

		void Update(f32 dt);
		BOOL IsFinished() const;

		// IEventInputKeyboardListener
		virtual void OnInputKeyboardPress(const EventInputKeyboard *ev);
		virtual void OnInputKeyboardRelease(const EventInputKeyboard *ev);

	protected:
		BOOL bFinished;
		s32 iOption;
		BOOL bWaitingFinish;

		f32 fNextX;
		f32 fNextY;
		f32 fPrevX;
		f32 fPrevY;

		SoundSource sfxChange;
		SoundSource sfxOk;

		Sprite sptBg;
		Sprite sptBase;
		Sprite sptTitle;

		Sprite sptControl;
		Sprite sptControlType;

		Sprite sptBgm;
		Sprite sptBgmVol;

		Sprite sptSfx;
		Sprite sptSfxVol;

		Sprite sptFullscreen;
		Sprite sptFullscreenCheck;

		Sprite sptExit;

		Sprite sptNext;
		Sprite sptPrev;

		void UpdateAnimation();
};

#endif // __OPTIONS_H__
