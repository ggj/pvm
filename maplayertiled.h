#ifndef __MAPLAYERTILED_H__
#define __MAPLAYERTILED_H__

#include "imaplayer.h"

class Tile;
class TileSprite;
class Map;

#define MAX_VIEW_SPRITES 1024 * 4 //256

class MapLayerTiled : public IMapLayer
{
	friend class Map;

	public:
		MapLayerTiled();
		virtual ~MapLayerTiled();

		virtual void Initialize(u32 tilesX, u32 tilesY);
		virtual void Reset();

		virtual void SetView(u32 tilesX, u32 tilesY);
		virtual void SetTileSize(Point2u tileSize);
		virtual void SetTileSet(const char *sprite);
		virtual void SetTileData(const u32 *data);

		virtual void SetWrap(BOOL b);
		virtual BOOL GetWrap() const;

		virtual f32 GetTileWidth() const;
		virtual f32 GetTileHeight() const;

		virtual Point2i ViewAt(Point2i pos);

		// IMapLayer
		virtual MapLayerTiled *AsTiled();

		// ISceneObject
		virtual void Update(f32 delta);
		virtual void Render();

	private:
		void UpdateTiles(u32 x, u32 y);

	private:
		SceneNode<MAX_VIEW_SPRITES> cScene;

		Tile **pTiles;
		TileSprite **pSprites;
		const u32 *pTileData;

		const char *pcTileSet;
		Sprite sptTileSet;

		s32 iPosX;
		s32 iPosY;
		s32 iOffsetX;
		s32 iOffsetY;

		u32 iTilesWidth;
		u32 iTilesHeight;
		u32 iViewTilesWidth;
		u32 iViewTilesHeight;
		u32 iViewTilesSize;
		Point2u ptiTileSize;
		//u32 iTileWidth;
		//u32 iTileHeight;
		u32 iMapWidth;
		u32 iMapHeight;
		u32 iViewWidth;
		u32 iViewHeight;

		BOOL bWrap;
};

#endif // __MAPLAYERTILED_H__
