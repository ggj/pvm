#ifndef __MAPLAYERMETADATA_H__
#define __MAPLAYERMETADATA_H__

#include "imaplayer.h"
#include <Box2D/Box2D.h>

#define MAX_METAOBJECTS 128
#define MAX_COLLISION	32

class IMetadataObject;

struct CollisionData
{
	IMetadataObject *obj;
	Rect4f overlap;
};

typedef Array<CollisionData, MAX_COLLISION> CollisionDataArray;
typedef CollisionDataArray* CollisionDataArrayPtr;

class MapLayerMetadata : public IMapLayer
{
	public:
		MapLayerMetadata();
		virtual ~MapLayerMetadata();

		virtual void Initialize(Point2u tileSize, u32 count, const LayerObjectHeader *data, b2World *world);
		virtual void Reset();

		virtual Point2i ViewAt(Point2i pos);
		virtual BOOL CheckHit(const Rect4f &area, CollisionDataArrayPtr col) const;

		/// Called to instantiate each metadata object.
		/*! For each object in a metadata layer, this method will be called to construct
			a customized metadata object. You should override this method to instantiate your
			own custom objects. When overriding this method, do not call the base method, as
			it will instantiate a new object and may leak.

			\param entry a struct of Layer Object basic information.
			\return An instance of a custom object from IMetadataObject type.
		*/
		virtual IMetadataObject *CreateObject(const LayerObjectHeader *entry, b2World *world);

		// IMapLayer
		MapLayerMetadata *AsMetadata();

		// ISceneObject
		virtual void Update(f32 delta);
		virtual void Render();

	private:
		SceneNode<MAX_METAOBJECTS> cScene;
		Array<IMetadataObject *, MAX_METAOBJECTS> arObjects;
		u32 iObjects;
		Point2u ptiTileSize;
};

#endif // __MAPLAYERMETADATA_H__
