#include "hud.h"
#include "assets.h"
#include "app.h"

Hud::Hud()
{
	sptLifesP1.Load(SPT_GAUGE);
	sptLifesP1.SetPosition(0, 0);
	sptLifesP1.SetPriority(100000);
	sptLifesP1.SetAnimation((u32)0);
	pScene->Add(&sptLifesP1);

	sptLifesP2.Load(SPT_GAUGE);
	sptLifesP2.SetPosition(1.0f - sptLifesP2.GetWidth(), 0);
	sptLifesP2.SetScaleX(-1);
	sptLifesP2.SetPriority(100000);
	sptLifesP2.SetAnimation((u32)1);
	pScene->Add(&sptLifesP2);
}

Hud::~Hud()
{
	pScene->Remove(&sptLifesP1);
	sptLifesP1.Unload();

	pScene->Remove(&sptLifesP2);
	sptLifesP2.Unload();
}

void Hud::SetFirstPlayerLifes(u32 value)
{
	if (value)
		sptLifesP1.SetCurrentFrame(value - 1);
}

void Hud::SetSecondPlayerLifes(u32 value)
{
	if (value)
		sptLifesP2.SetCurrentFrame(value - 1);
}
