#ifndef __SPAWNEROBJECT_H__
#define __SPAWNEROBJECT_H__

#include "main.h"
#include "imetadataobject.h"

class SpawnerObject : public IMetadataObject
{
	public:
		SpawnerObject();
		virtual ~SpawnerObject();

		// ISceneObject
		virtual void Update(f32 delta);
		virtual void Render();
};

#endif // __SPAWNEROBJECT_H__
