#include "credits.h"
#include "app.h"
#include "assets.h"

Credits::Credits()
	: bFinished(FALSE)
	, sptBg()
	, sptPanda()
	, sptMaya()
	, sfxRun()
{
	pInput->AddPointerListener(this);
	pInput->AddKeyboardListener(this);

	sptBg.Load(SPT_CREDITSBG);
	pScene->Add(&sptBg);

	sptPanda.Load(SPT_PANDA);
	sptPanda.SetPriority(1002);
	sptPanda.SetPosition(0.61f, 0.13f);
	sptPanda.SetAnimation("run");
	pScene->Add(&sptPanda);

	sptMaya.Load(SPT_MAIA);
	sptMaya.SetPriority(1000);
	sptMaya.SetAnimation("run");
	sptMaya.SetPosition(0.33f, 0.13f);
	pScene->Add(&sptMaya);

	sfxRun.Load(SFX_STEPS);
	sfxRun.Play();
	//sfxRun.SetVolume(0.1f);
	pSoundSystem->Add(&sfxRun);
}

Credits::~Credits()
{
	sptBg.Unload();
	sfxRun.Unload();
	sptMaya.Unload();
	sptPanda.Unload();
	pScene->Remove(&sptBg);
	pScene->Remove(&sptMaya);
	pScene->Remove(&sptPanda);
	pInput->RemoveKeyboardListener(this);
	pInput->RemovePointerListener(this);
}

void Credits::Update(f32 dt)
{
}

void Credits::OnInputKeyboardPress(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	bFinished = TRUE;
}

void Credits::OnInputPointerRelease(const EventInputPointer *ev)
{
	bFinished = TRUE;
}

BOOL Credits::IsFinished() const
{
	return bFinished;
}
