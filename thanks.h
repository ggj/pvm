#ifndef __THANKS_H__
#define __THANKS_H__

#include <Seed.h>
using namespace Seed;

class Thanks : public IEventInputKeyboardListener, public IEventInputPointerListener
{
	public:
		Thanks();
		virtual ~Thanks();

		void Update(f32 dt);
		BOOL IsFinished() const;

		// IEventInputKeyboardListener
		virtual void OnInputKeyboardPress(const EventInputKeyboard *ev);

		// IEventInputPointerListener
		virtual void OnInputPointerRelease(const EventInputPointer *ev);

	protected:
		BOOL bFinished;
		f32 fElapsed;
		Sprite sptBg;
};

#endif // __THANKS_H__
