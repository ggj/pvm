#include "credits.h"
#include "main.h"
#include "assets.h"
#include "tutorial.h"

Tutorial::Tutorial()
	: bFinished(FALSE)
	, bBlocked(TRUE)
	, fElapsed(0.0f)
{
	pInput->AddPointerListener(this);
	pInput->AddKeyboardListener(this);
	sptBg.Load(SPT_TUTORIAL);
	pScene->Add(&sptBg);
}

Tutorial::~Tutorial()
{
	sptBg.Unload();
	pScene->Remove(&sptBg);
	pInput->RemoveKeyboardListener(this);
	pInput->RemovePointerListener(this);
	pResourceManager->GarbageCollect();
}

void Tutorial::Update(f32 dt)
{
	fElapsed += dt;

	if (fElapsed > 0.35f)
		bBlocked = FALSE;
}

void Tutorial::OnInputKeyboardPress(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	if (!bBlocked)
		bFinished = TRUE;
}

void Tutorial::OnInputPointerRelease(const EventInputPointer *ev)
{
	if (!bBlocked)
		bFinished = TRUE;
}