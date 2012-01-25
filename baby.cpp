#include "main.h"
#include "baby.h"
#include "assets.h"

#include "maplayermetadata.h"

Baby::Baby(b2World *world) : Actor(world)
{
	sptActor.SetPriority(PRIORITY_ENTITY);
	pScene->Add(&sptActor);	
}

Baby::~Baby()
{
	pScene->Remove(&sptActor);
	sptActor.Unload();
}

void Baby::Load(eTeam team)
{
	switch (team)
	{
		case TeamPanda:
		{
			sptActor.Load(SPT_BABY);
			sptActor.SetAnimation("baby_panda");
		}
		break;

		case TeamMaya:
		{
			sptActor.Load(SPT_BABY);
			sptActor.SetAnimation("baby_maya");
		}
		break;

		default:
		break;
	}

	this->SetWidth(sptActor.GetWidth() * pScreen->GetWidth() - PLAYER_BORDER * 2.0f);
	this->SetHeight(sptActor.GetHeight() * pScreen->GetHeight() - PLAYER_BORDER * 2.0f);
}

void Baby::Update(f32 dt, MapLayerMetadata *col)
{
	Actor::Update(dt);

	/*CollisionDataArray arrcol;

	this->SetPosition(sptActor.GetX() * pScreen->GetWidth() + PLAYER_BORDER, sptActor.GetY() * pScreen->GetHeight() + PLAYER_BORDER);
	float lastX = fLastX * pScreen->GetWidth();
	float lastY = fLastY * pScreen->GetHeight();

	Rect4f playerCollision;

	bool bColliding = col && col->CheckHit(this->GetBoundingBox(), &arrcol);

	if (bColliding)
	{
		CollisionData *data = &arrcol[0];

		float repel = FORCE_CAP / 2 * pScreen->GetWidth();

		bool found = false;

		for (u32 i = 0; i < arrcol.Size(); i++)
		{
			data = &arrcol[i];

			if (!(lastX + GetBoundingBox().width - repel <=  data->obj->GetBoundingBox().x || lastX + repel >= data->obj->GetBoundingBox().x +  data->obj->GetBoundingBox().width))
			{
				if (!(lastY + GetBoundingBox().height - repel <=  data->obj->GetBoundingBox().y || lastY + repel >= data->obj->GetBoundingBox().y +  data->obj->GetBoundingBox().height))
				{
					found = true;
					break;
				}
			}
		}

		if (!found)
		{
			data = &arrcol[0];
		}

		if (lastX + GetBoundingBox().width - repel <= data->obj->GetBoundingBox().x || lastX + repel >= data->obj->GetBoundingBox().x + data->obj->GetBoundingBox().width)
		{
			sptActor.AddX( -(vDir.x + fAForce) * ((data->overlap.width + repel) / pScreen->GetWidth()));
			fAForce *= -1.0f;
			vDir.x = 0.0f;
		}
		else
		{
			sptActor.AddY( -(vDir.y + fGForce) * ((data->overlap.height) / pScreen->GetHeight()));
			fGForce *= -0.5;
			vDir.y = 0.0f;
		}
	}*/

	if (body)
	{
	    b2Vec2 pos = body->GetPosition();
	    sptActor.SetPosition(pos.x * PIXEL2METER - sptActor.GetWidth() * 0.5f, pos.y * PIXEL2METER * -1.0f - sptActor.GetHeight() * 0.5f);
	}
	this->SetPosition(sptActor.GetX() * pScreen->GetWidth() + PLAYER_BORDER, sptActor.GetY() * pScreen->GetHeight() + PLAYER_BORDER);
}

