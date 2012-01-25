#ifndef __COLLISIONOBJECT_H__
#define __COLLISIONOBJECT_H__

#include "main.h"
#include "imetadataobject.h"

#include <Box2D/Box2D.h>

#define PIXEL2METER 0.0234375f
#define BOXSIZE 0.5f

#define COLLISION_GROUND 0x0001
#define COLLISION_PLAYER 0x0002
#define COLLISION_OBJECT 0x0004
#define COLLISION_ALL    0xFFFF

class CollisionObject : public IMetadataObject
{
	public:
		CollisionObject(b2World *world);
		virtual ~CollisionObject();

		// ISceneObject
		virtual void Update(f32 delta);
		virtual void Render();

		void CreateDinamycBody(f32 x, f32 y, f32 width, f32 height, u16 category, u16 mask);
		void CreateStaticBody(f32 x, f32 y, f32 width, f32 height);

	protected:
		b2World *world;
		b2Body *body;
		b2BodyDef bodyDef;
		b2PolygonShape shape;
		b2FixtureDef fixtureDef;

	private:
		void CreateBody(f32 x, f32 y, f32 width, f32 height, bool dynamic, u16 category = COLLISION_GROUND, u16 mask = COLLISION_GROUND);
};

#endif // __COLLISIONOBJECT_H__
