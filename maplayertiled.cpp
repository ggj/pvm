#include "maplayertiled.h"
#include "tile.h"

#define TILE(x, y)		pTiles[(x) + (iTilesWidth * (y))]
#define SPRITE(x, y)	pSprites[(x) + (iViewTilesWidth * (y))]

MapLayerTiled::MapLayerTiled()
	: pTiles(NULL)
	, pSprites(NULL)
	, pTileData(NULL)
	, pcTileSet(NULL)
	, iPosX(-1)
	, iPosY(-2)
	, iOffsetX(-0)
	, iOffsetY(-0)
	, iTilesWidth(0)
	, iTilesHeight(0)
	, iViewTilesWidth(0)
	, iViewTilesHeight(0)
	, iViewTilesSize(0)
	//, iTileWidth(32)
	//, iTileHeight(32)
	, ptiTileSize(0, 0)
	, iMapWidth(1)
	, iMapHeight(1)
	, iViewWidth(1)
	, iViewHeight(1)
	, bWrap(FALSE)
{
}

MapLayerTiled::~MapLayerTiled()
{
	this->Reset();
}

void MapLayerTiled::Reset()
{
	if (pTiles)
	{
		for (u32 y = 0; y < iTilesHeight; y++)
		{
			for (u32 x = 0; x < iTilesWidth; x++)
			{
				Delete(TILE(x, y));
			}
		}

		pMemoryManager->Free(pTiles);
	}
	pTiles = NULL;

	if (pSprites)
	{
		for (u32 y = 0; y < iViewTilesHeight; y++)
		{
			for (u32 x = 0; x < iViewTilesWidth; x++)
			{
				Delete(SPRITE(x, y));
			}
		}

		pMemoryManager->Free(pSprites);
	}
	pSprites = NULL;

	pTileData = NULL;
}

void MapLayerTiled::Initialize(u32 tilesWidth, u32 tilesHeight)
{
	tilesWidth = tilesWidth < iViewTilesWidth ? iViewTilesWidth : tilesWidth;
	tilesHeight = tilesHeight < iViewTilesHeight ? iViewTilesHeight : tilesHeight;

	if (pTiles)
	{
		for (u32 y = 0; y < iTilesHeight; y++)
		{
			for (u32 x = 0; x < iTilesWidth; x++)
			{
				Delete(TILE(x, y));
			}
		}

		pMemoryManager->Free(pTiles);
	}

	iTilesWidth = tilesWidth;
	iTilesHeight = tilesHeight;
	pTiles = (Tile **)pMemoryManager->Alloc(iTilesWidth * iTilesHeight * sizeof(Tile *), pDefaultPool, "Grid", "MapLayerTiled");

	for (u32 y = 0; y < iTilesHeight; y++)
	{
		for (u32 x = 0; x < iTilesWidth; x++)
		{
			Tile *tile = New(Tile);
			TILE(x, y) = tile;

			if (pTileData)
				tile->SetType(pTileData[(x) + (iTilesWidth * (y))]);
			else
				tile->SetType(0);
		}
	}

	iMapWidth = ptiTileSize.x * iTilesWidth;
	iMapHeight = ptiTileSize.y * iTilesHeight;
	iViewWidth = ptiTileSize.x * iViewTilesWidth;
	iViewHeight = ptiTileSize.y * iViewTilesHeight;

	this->UpdateTiles(0, 0);
}

void MapLayerTiled::SetTileData(const u32 *data)
{
	pTileData = data;

	if (pTiles)
	{
		for (u32 y = 0; y < iTilesHeight; y++)
		{
			for (u32 x = 0; x < iTilesWidth; x++)
			{
				Tile *tile = TILE(x, y);

				if (pTileData)
					tile->SetType(pTileData[(x) + (iTilesWidth * (y))]);
				else
					tile->SetType(0);
			}
		}
	}
}

void MapLayerTiled::SetView(u32 viewWidth, u32 viewHeight)
{
	cScene.Reset();
	if (pSprites)
	{
		for (u32 y = 0; y < iViewTilesHeight; y++)
		{
			for (u32 x = 0; x < iViewTilesWidth; x++)
			{
				Delete(SPRITE(x, y));
			}
		}

		pMemoryManager->Free(pSprites);
	}

	iViewTilesWidth = viewWidth + 1;
	iViewTilesHeight = viewHeight + 1;

	iTilesWidth = iTilesWidth < viewWidth ? viewWidth : iTilesWidth;
	iTilesHeight = iTilesHeight < viewHeight ? viewHeight : iTilesHeight;
    
	iViewTilesSize = iViewTilesWidth * iViewTilesHeight;
	pSprites = (TileSprite **)pMemoryManager->Alloc(iViewTilesSize * sizeof(TileSprite *), pDefaultPool, "View", "MapLayerTiled");

	f32 sptX = static_cast<f32>(ptiTileSize.x) / static_cast<f32>(pScreen->GetWidth());
	f32 sptY = static_cast<f32>(ptiTileSize.y) / static_cast<f32>(pScreen->GetHeight());

	u32 i = 0;
	for (u32 y = 0; y < iViewTilesHeight; y++)
	{
		for (u32 x = 0; x < iViewTilesWidth; x++)
		{
			TileSprite *spt = New(TileSprite);
			SPRITE(x, y) = spt;

			if (pcTileSet)
				spt->Load(pcTileSet);

			spt->SetPosition(x * sptX, y * sptY);
			spt->SetVisible(TRUE);
			//spt->SetBlending(Seed::BlendModulate);
			//spt->SetColor(1.0f, 1.0f, 1.0f, 0.5f);
			cScene.Add(spt);
			i++;
		}
	}

	iMapWidth = ptiTileSize.x * iTilesWidth;
	iMapHeight = ptiTileSize.y * iTilesHeight;
	iViewWidth = ptiTileSize.x * iViewTilesWidth;
	iViewHeight = ptiTileSize.y * iViewTilesHeight;

	for (u32 i = 0; i < iViewTilesSize; i++)
	{
		pSprites[i]->Update(0.0f);
	}
}

Point2i MapLayerTiled::ViewAt(Point2i pos)
{
	s32 x = pos.x;
	s32 y = pos.y;

	if (bWrap)
	{
		if (x < 0)
			x = iMapWidth + x;

		if (y < 0)
			y = iMapHeight + y;

		if (u32(x) > iMapWidth)
			x -= iMapWidth;

		if (u32(y) > iMapHeight)
			y -= iMapHeight;
	}
	else
	{
		s32 xd = static_cast<s32>(iMapWidth - iViewWidth);
		s32 yd = static_cast<s32>(iMapHeight - iViewHeight);

		if (x < 0)
			x = 0;

		if (y < 0)
			y = 0;

		if (x > xd + (s32)ptiTileSize.x - 1)
			x = xd + ptiTileSize.x - 1;

		if (y > yd + (s32)ptiTileSize.y - 1)
			y = yd + ptiTileSize.y - 1;
	}

	Point2i ret(x, y);

	s32 newX = x / static_cast<s32>(ptiTileSize.x);
	s32 newY = y / static_cast<s32>(ptiTileSize.y);

	iOffsetX = x - (newX * ptiTileSize.x);//x & (iTileSize - 1);
	iOffsetY = y - (newY * ptiTileSize.y);//y & (iTileSize - 1);

	f32 ox = -static_cast<f32>(iOffsetX) / static_cast<f32>(pScreen->GetWidth());
	f32 oy = -static_cast<f32>(iOffsetY) / static_cast<f32>(pScreen->GetHeight());

	cScene.SetPosition(ox, oy);

	if (newX != iPosX || newY != iPosY)
	{
		iPosX = newX;
		iPosY = newY;

		this->UpdateTiles(iPosX, iPosY);
	}

	return ret;
}

void MapLayerTiled::Update(f32 dt)
{
	for (u32 i = 0; i < iViewTilesSize; i++)
	{
		pSprites[i]->Update(dt);
	}
}

void MapLayerTiled::Render()
{
	for (u32 i = 0; i < iViewTilesSize; i++)
	{
		pSprites[i]->Render();
	}
}

void MapLayerTiled::SetTileSet(const char *sprite)
{
	pcTileSet = sprite;
	iMapWidth = 1;
	iMapHeight = 1;
	iViewWidth = 1;
	iViewHeight = 1;

	if (sprite)
	{
		sptTileSet.Unload();
		sptTileSet.Load(sprite);
		sptTileSet.GetTexture()->SetFilter(Seed::TextureFilterTypeMin, Seed::TextureFilterNearest);
		sptTileSet.GetTexture()->SetFilter(Seed::TextureFilterTypeMag, Seed::TextureFilterNearest);

		iMapWidth = ptiTileSize.x * iTilesWidth;
		iMapHeight = ptiTileSize.y * iTilesHeight;
		iViewWidth = ptiTileSize.x * iViewTilesWidth;
		iViewHeight = ptiTileSize.y * iViewTilesHeight;

		if (pSprites)
		{
			for (u32 y = 0; y < iViewTilesHeight; y++)
			{
				for (u32 x = 0; x < iViewTilesWidth; x++)
				{
					TileSprite *spt = SPRITE(x, y);

					if (spt)
						spt->Load(pcTileSet);
				}
			}
		}
	}

	this->UpdateTiles(iPosX > 0 ? iPosX : 0, iPosY > 0 ? iPosY : 0);
}

void MapLayerTiled::SetTileSize(Point2u tileSize)
{
	ptiTileSize = tileSize;
}

f32 MapLayerTiled::GetTileWidth() const
{
	return sptTileSet.GetWidth();
}

f32 MapLayerTiled::GetTileHeight() const
{
	return sptTileSet.GetHeight();
}

void MapLayerTiled::SetWrap(BOOL b)
{
	bWrap = b;
}

BOOL MapLayerTiled::GetWrap() const
{
	return bWrap;
}

void MapLayerTiled::UpdateTiles(u32 posX, u32 posY)
{
	for (u32 y = 0; y < iViewTilesHeight; y++)
	{
		for (u32 x = 0; x < iViewTilesWidth; x++)
		{
			TileSprite *spt = SPRITE(x, y);
			u32 tx = 0;
			u32 ty = 0;

			if (x + posX < iTilesWidth)
			{
				tx = x + posX;
			}
			else
			{
				tx = x + posX - iTilesWidth;
			}

			if (y + posY < iTilesHeight)
			{
				ty = y + posY;
			}
			else
			{
				ty = y + posY - iTilesHeight;
			}

			Tile *tile = TILE(tx, ty);
			spt->SetTile(tile);
		}
	}
}

MapLayerTiled *MapLayerTiled::AsTiled()
{
	return this;
}
