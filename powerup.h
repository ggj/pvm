#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "app.h"
#include "actor.h"

enum PowerUpType
{
	PU_WEIGHT = 6,
	PU_GRAVITY = 9,
	PU_CONTROL = 12,
	PU_SHIELD = 13
};

class MapLayerMetadata;

class PowerUp : public Actor
{
	public:
		PowerUp(b2World *world,PowerUpType eType);
		virtual ~PowerUp();

		virtual void Update(f32 dt, MapLayerMetadata *pCollision);

		PowerUpType GetType() { return eType; };

	protected:
		PowerUpType eType;
};

#endif
