#ifndef __CREDITS_H__
#define __CREDITS_H__

#include <Seed.h>
using namespace Seed;

class Credits : public IEventInputKeyboardListener, public IEventInputPointerListener
{
	public:
		Credits();
		virtual ~Credits();

		void Update(f32 dt);
		BOOL IsFinished() const;

		// IEventInputKeyboardListener
		virtual void OnInputKeyboardPress(const EventInputKeyboard *ev);

		// IEventInputPointerListener
		virtual void OnInputPointerRelease(const EventInputPointer *ev);

	protected:
		BOOL bFinished;

		Sprite sptBg;
		Sprite sptPanda;
		Sprite sptMaya;
		SoundSource sfxRun;
};

#endif
