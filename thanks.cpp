#include "main.h"
#include "assets.h"
#include "thanks.h"

Thanks::Thanks()
	: bFinished(FALSE)
	, fElapsed(0.0f)
	, sptBg()
{
	pInput->AddPointerListener(this);
	pInput->AddKeyboardListener(this);
	sptBg.Load(SPT_THANKS);
	sptBg.SetPriority(PRIORITY_THANKS);
	pScene->Add(&sptBg);
}

Thanks::~Thanks()
{
	pInput->RemoveKeyboardListener(this);
	pInput->RemovePointerListener(this);
	pScene->Reset();
}

void Thanks::Update(f32 dt)
{
	fElapsed += dt;

	if (fElapsed > 3.0f)
		bFinished = TRUE;
}

void Thanks::OnInputKeyboardPress(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	bFinished = TRUE;
}

void Thanks::OnInputPointerRelease(const EventInputPointer *ev)
{
	bFinished = TRUE;
}

BOOL Thanks::IsFinished() const
{
	return bFinished;
}
