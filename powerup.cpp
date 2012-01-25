#include "powerup.h"
#include "assets.h"
#include "app.h"
#include "maplayermetadata.h"

PowerUp::PowerUp(b2World *world, PowerUpType type) : Actor(world),
	eType(type)
{
	sptActor.Load(SPT_POWERUP_ICONS);
	sptActor.SetAnimation((u32)eType);

	this->SetWidth(sptActor.GetWidth() * pScreen->GetWidth() - PLAYER_BORDER * 2.0f);
	this->SetHeight(sptActor.GetHeight() * pScreen->GetHeight() - PLAYER_BORDER * 2.0f);

	sptActor.SetPriority(PRIORITY_ENTITY);
	pScene->Add(&sptActor);
}

PowerUp::~PowerUp()
{
	pScene->Remove(&sptActor);
	sptActor.Unload();
}

void PowerUp::Update(f32 dt, MapLayerMetadata *pCollision)
{
	Actor::Update(dt);

	if (body)
	{
		b2Vec2 pos = body->GetPosition();
		sptActor.SetPosition(pos.x * PIXEL2METER - sptActor.GetWidth() * 0.5f, pos.y * PIXEL2METER * -1.0f - sptActor.GetHeight() * 0.5f);
	}

	this->SetPosition(sptActor.GetX() * pScreen->GetWidth() + PLAYER_BORDER, sptActor.GetY() * pScreen->GetHeight() + PLAYER_BORDER);
}
