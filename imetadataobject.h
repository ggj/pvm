#ifndef __IMETADATAOBJECT_H__
#define __IMETADATAOBJECT_H__

#include "main.h"

class IMetadataObject : public ISceneObject
{
	public:
		IMetadataObject();
		virtual ~IMetadataObject();

		virtual void SetPosition(f32 x, f32 y);
		virtual void SetWidth(f32 w);
		virtual void SetHeight(f32 h);

		virtual const Rect4f &GetBoundingBox() const;
		virtual BOOL CheckHit(const Rect4f &area, Rect4f &overlap) const;

		void SetNameId(u32 nameId);
		u32 GetNameId() const;
		const char *GetName() const;

		void SetTypeId(u32 typeId);
		u32 GetTypeId() const;
		const char *GetType() const;

		void LoadProperties(u32 propId);
		const char *GetProperties() const;

	protected:
		const char *pcName;
		const char *pcType;
		const char *pcProperties;

		Rect4f cArea;

		u32 iNameId;
		u32 iTypeId;
};

#endif // __IMETADATAOBJECT_H__
