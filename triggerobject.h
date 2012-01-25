#ifndef __TRIGGER_H__
#define __TRIGGER_H__

#include "main.h"
#include "imetadataobject.h"

class TriggerObject : public IMetadataObject
{
	public:
		TriggerObject();
		virtual ~TriggerObject();

		// ISceneObject
		virtual void Update(f32 delta);
		virtual void Render();
};

#endif // __TRIGGER_H__
