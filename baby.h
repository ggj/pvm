#ifndef __BABY_H__
#define __BABY_H__

#include "app.h"
#include "actor.h"

class MapLayerMetadata;

class Baby : public Actor
{
	public:
		Baby(b2World *world);
		virtual ~Baby();

		virtual void Load(eTeam team);
		virtual void Update(f32 dt, MapLayerMetadata *collision);

	private:
		SEED_DISABLE_COPY(Baby);
};

#endif
