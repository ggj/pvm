#ifndef __HUD_H__
#define __HUD_H__

#include <Seed.h>
using namespace Seed;

class Hud
{
	public:
		Hud();
		virtual ~Hud();

		void SetFirstPlayerLifes(u32 value);
		void SetSecondPlayerLifes(u32 value);

	protected:
		Sprite sptLifesP1;
		Sprite sptLifesP2;
};

#endif
