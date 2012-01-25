#ifndef __MENU_H__
#define __MENU_H__

#include "main.h"

enum eMenuOption
{
	OptionsStart,
	OptionPlay = OptionsStart,
	OptionOptions,
	OptionCredits,
	OptionQuit,
	OptionsEnd = OptionQuit,
};

class Menu : public IEventInputKeyboardListener, public IEventWidgetListener
{
	public:
		Menu();
		virtual ~Menu();

		void Update(f32 dt);

		BOOL IsFinished() const;
		eMenuOption GetOption() const;

		// IEventInputKeyboardListener
		virtual void OnInputKeyboardPress(const EventInputKeyboard *ev);

		// IEventWidgetListener
		virtual void OnWidgetRelease(const EventWidget *ev);
		virtual void OnWidgetRollOver(const EventWidget *ev);

	protected:
		BOOL bFinished;
		s32 iSelected;
		BOOL bWaitingFinish;

		SoundSource sfxChange;
		SoundSource sfxOk;

		Sprite sptBg;
		Sprite sptStart;
		Sprite sptCredits;
		Sprite sptOptions;
		Sprite sptQuit;
		Sprite sptPanda;
		Sprite sptMaya;

		Button btnStart;
		Button btnCredits;
		Button btnOptions;
		Button btnQuit;

		f32 fAnimPosY;

		void UpdateAnimation();
};

#endif
