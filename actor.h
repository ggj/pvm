#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "main.h"
#include "collisionobject.h"

#define PLAYER_BORDER	2.0f
#define THRUST_POWER_X 	0.10f
#define THRUST_POWER_Y 	0.30f

class Actor : public CollisionObject
{
	public:
		Actor(b2World *world);
		virtual ~Actor();

		virtual void Update(f32 dt);
		virtual Sprite &GetSprite();

		virtual void SetInvertedAxis(BOOL b);
		virtual void SetGravityModifier(f32 mod);
		virtual void SetHeavy(BOOL b);

	protected:
		Sprite sptActor;

		f32 fLastX;
		f32 fLastY;
		f32 fGravityModifier;

		BOOL bInvertAxis;
		BOOL bEnableWeight;

		Point2f vDir;
		Point2f vController;
};

#endif // __ACTOR_H__
