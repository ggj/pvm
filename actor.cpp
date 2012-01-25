#include "actor.h"

Actor::Actor(b2World *world)
	: CollisionObject(world)
	, sptActor()
	, fLastX(0.0f)
	, fLastY(0.0f)
	, fGravityModifier(0.0f)
	, bInvertAxis(FALSE)
	, bEnableWeight(FALSE)
	, vDir()
	, vController()
{
	pScene->Add(this);
}

Actor::~Actor()
{
	pScene->Remove(this);
}

void Actor::Update(f32 dt)
{
	Point2f vThrust;
	vThrust.x = bInvertAxis ? -vController.x : vController.x;

	if (bEnableWeight)
		vThrust.x = 0;

	vThrust.y = vController.y;

	f32 fThrustX = (THRUST_POWER_X + fGravityModifier) * dt;
	f32 fThrustY = (THRUST_POWER_Y + fGravityModifier) * dt;

	vThrust.x *= fThrustX;
	vThrust.y *= fThrustY;

	if (body)
	{
		vThrust.x /= PIXEL2METER;
		vThrust.y /= PIXEL2METER;
		body->ApplyLinearImpulse(b2Vec2(vThrust.x, vThrust.y), b2Vec2(0.0f, 0.0f));
	}

	bool updateBodyX = false;
	bool updateBodyY = false;

	f32 distanceY = 1.0f / pScreen->GetHeight();

	if (sptActor.GetX() + sptActor.GetWidth() > 1.0f)
	{
		sptActor.SetX(1.0f - sptActor.GetWidth());
		updateBodyX = true;
	}

	if (sptActor.GetX() < 0)
	{
		sptActor.SetX(0.0f);
		updateBodyX = true;
	}

	if (sptActor.GetY() + sptActor.GetHeight() > 1.0f)
	{
		sptActor.SetY(1.0f - distanceY);
		updateBodyY = true;
	}

	if (sptActor.GetY() < 0)
	{
		sptActor.SetY(sptActor.GetHeight());
		updateBodyY = true;
	}

	if (body && (updateBodyX || updateBodyY))
	{

		f32 sizeX = pScreen->GetWidth() * PIXEL2METER;
		f32 sizeY = pScreen->GetHeight() * PIXEL2METER;

		f32 b2x = sptActor.GetX() * pScreen->GetWidth() / sizeX;
		f32 b2y = -(sptActor.GetY() * pScreen->GetHeight() / sizeY);

		f32 b2w = sptActor.GetWidth() * pScreen->GetWidth() / sizeX;
		f32 b2h = sptActor.GetHeight() * pScreen->GetHeight() / sizeY;

		f32 x = updateBodyX ?  b2x + b2w * 0.5f : body->GetPosition().x;
		f32 y = updateBodyY ?  b2y + b2h * 0.5f : body->GetPosition().y;

		body->SetTransform(b2Vec2(x, y), body->GetAngle());
		body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	}
}

Sprite &Actor::GetSprite()
{
	return sptActor;
}

void Actor::SetInvertedAxis(BOOL b)
{
	bInvertAxis = b;
}

void Actor::SetGravityModifier(f32 mod)
{
	fGravityModifier = mod;
}

void Actor::SetHeavy(BOOL b)
{
	bEnableWeight = b;
}
