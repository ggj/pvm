#ifndef __TUTORIAL_H__
#define __TUTORIAL_H__

#include <Seed.h>
using namespace Seed;

class Tutorial : public IEventInputKeyboardListener, public IEventInputPointerListener
{
	public:
		Tutorial();
		virtual ~Tutorial();

		void Update(f32 dt);

		BOOL IsFinished() { return bFinished; };
	
	protected:
		BOOL bFinished;
		BOOL bBlocked;
		f32 fElapsed;
		Sprite sptBg;

		// IEventInputKeyboardListener
		virtual void OnInputKeyboardPress(const EventInputKeyboard *ev);
		
		// IEventInputPointerListener
		virtual void OnInputPointerRelease(const EventInputPointer *ev);
};

#endif // __TUTORIAL_H__