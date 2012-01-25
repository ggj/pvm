#ifndef __INTRO_H__
#define __INTRO_H__

#include <Seed.h>
using namespace Seed;

class Intro : public IEventInputKeyboardListener, public IEventWidgetListener
{
	public:
		Intro();
		virtual ~Intro();

		void Update(f32 dt);
		BOOL IsFinished() const;

		// IEventInputKeyboardListener
		virtual void OnInputKeyboardPress(const EventInputKeyboard *ev);
		
		// IEventWidgetListener
		virtual void OnWidgetRelease(const EventWidget *ev);

	protected:
		BOOL bFinished;
		BOOL bWaitingFinish;
		BOOL bDir;
		f32 fAlpha;

		SoundSource sfxOk;

		Sprite sptBg;
		Button btnStart;
};

#endif // __INTRO_H__
