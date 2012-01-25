#include "collisionobject.h"

CollisionObject::CollisionObject(b2World *w)
	: world(w)
	, body(NULL)
{
}

CollisionObject::~CollisionObject()
{
	if (world && body)
	{
		world->DestroyBody(body);
	}

	body = NULL;
	world = NULL;
}

void CollisionObject::Update(f32 dt)
{
}

void CollisionObject::Render()
{
#if DEBUG
	//pRendererDevice->DrawRect(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight(), PIXEL_COLOR(255, 0, 255, 255));
#endif

	/*
	if (body)
	{
		b2Vec2 pos = body->GetPosition();

		if (body->GetType() == b2_dynamicBody)
		{
			pRendererDevice->DrawRect(pos.x * PIXEL2METER - GetWidth() * 0.5f, pos.y * PIXEL2METER * -1.0f - GetHeight() * 0.5f, GetWidth(), GetHeight(), PIXEL_COLOR(0, 255, 0, 255));
		}
		else
		{
			pRendererDevice->DrawRect(pos.x * PIXEL2METER - GetWidth() * 0.5f, pos.y * PIXEL2METER * -1.0f - GetHeight() * 0.5f, GetWidth(), GetHeight(), PIXEL_COLOR(0, 0, 255, 255));
		}

		pRendererDevice->DrawRect(pos.x * PIXEL2METER - 5.0f * pixelX, pos.y * PIXEL2METER * -1.0f - 5.0f * pixelY, pixelX * 10.0f, pixelY * 10.0f, PIXEL_COLOR(255, 255, 0, 255), true);
	}
	else
	{
		pRendererDevice->DrawRect(GetX(), GetY(), GetWidth(), GetHeight(), PIXEL_COLOR(255, 0, 0, 255));
	}
	*/
}

void CollisionObject::CreateDinamycBody(f32 x, f32 y, f32 width, f32 height, u16 category, u16 mask)
{
	this->CreateBody(x, y, width, height, true, category, mask);
}

void CollisionObject::CreateStaticBody(f32 x, f32 y, f32 width, f32 height)
{
	this->CreateBody(x, y, width, height, false);
}

void CollisionObject::CreateBody(f32 x, f32 y, f32 width, f32 height, bool dynamic, u16 category, u16 mask)
{
	f32 sizeX = pScreen->GetWidth() * PIXEL2METER;
	f32 sizeY = pScreen->GetHeight() * PIXEL2METER;

	f32 b2x = x * pScreen->GetWidth() / sizeX;
	f32 b2y = -(y * pScreen->GetHeight() / sizeY);

	f32 b2w = width * pScreen->GetWidth() / sizeX;
	f32 b2h = height * pScreen->GetHeight() / sizeY;

	if (dynamic)
	{
		bodyDef.type = b2_dynamicBody;
	}
	else
	{
		bodyDef.type = b2_staticBody;
	}

	bodyDef.position.Set(b2x + b2w * 0.5f, b2y + b2h * 0.5f);
	bodyDef.fixedRotation = true;

	if (!body)
	{
		body = world->CreateBody(&bodyDef);
	}
	else
	{
		body->SetType(b2_dynamicBody);
	}

	shape.SetAsBox(b2w * BOXSIZE, b2h * BOXSIZE);
	fixtureDef.shape = &shape;

	if (dynamic)
	{
		fixtureDef.density = 0.0f;
		fixtureDef.friction = 0.0f;
		fixtureDef.restitution = 0.3f;

		fixtureDef.filter.categoryBits = category;
		fixtureDef.filter.maskBits = mask;
	}
	else
	{
		fixtureDef.density = 0.0f;
		fixtureDef.friction = 0.05f;
		fixtureDef.restitution = 0.0f;

		fixtureDef.filter.categoryBits = COLLISION_GROUND;
		fixtureDef.filter.maskBits = COLLISION_ALL;
	}

	body->CreateFixture(&fixtureDef);
}
