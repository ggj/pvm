#ifndef __MAP_H__
#define __MAP_H__

#include "main.h"
#include <Box2D/Box2D.h>

#define SEED_MAP_LAYERS_MAX		128

class IMapLayer;

class Map : public IResource, public ISceneObject
{
	public:
		Map(b2World *world);
		virtual ~Map();

		virtual void Reset();

		virtual u32 AddLayerTiled();
		virtual u32 AddLayerMetadata();
		virtual u32 AddLayerMosaic();

		virtual IMapLayer *GetLayerAt(u32 index);
		virtual IMapLayer *GetLayerByName(const char *name);

		// ISceneObject
		virtual void Update(f32 delta);
		virtual void Render();

		// IResource
		using IResource::Load;
		virtual BOOL Load(const char *filename, ResourceManager *res, IMemoryPool *pool);
		virtual BOOL Unload();

		// IObject
		virtual int GetObjectType() const;
		virtual const char *GetObjectName() const;

	private:
		enum eLayerType
		{
			LayerTypeTiled,
			LayerTypeMetadata,
			LayerTypeMosaic,
			LayerTypeMax,
		};

		SceneNode<SEED_MAP_LAYERS_MAX> cMapLayers;
		Array<IMapLayer *, SEED_MAP_LAYERS_MAX> arLayers;
		File	stFile;

		u32 iViewWidthInTiles;
		u32 iViewHeightInTiles;
		u32 iWidthInTiles;
		u32 iHeightInTiles;
		Point2u ptiTileSize;
		//u32 iTileWidth;
		//u32 iTileHeight;
		u32 iLayerCount;

		f32 fTileWidth;
		f32 fTileHeight;

		b2World *world;
};

#endif // __MAP_H__
