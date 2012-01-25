#include "map.h"
#include "imaplayer.h"
#include "maplayertiled.h"
#include "maplayermetadata.h"
#include "maplayermosaic.h"

Map::Map(b2World *world)
	: arLayers()
	, stFile()
	, iWidthInTiles(0)
	, iHeightInTiles(0)
	//, iTileWidth(0)
	//, iTileHeight(0)
	, ptiTileSize(0, 0)
	, iLayerCount(0)
	, fTileWidth(0.0f)
	, fTileHeight(0.0f)
{
	arLayers.Truncate();
	cMapLayers.SetParent(this);

	this->world = world;
}

Map::~Map()
{
	this->Reset();

	world = NULL;
}

INLINE BOOL Map::Load(const char *filename, ResourceManager *res, IMemoryPool *pool)
{
	ASSERT_NULL(filename);
	ASSERT_NULL(res);
	ASSERT_NULL(pool);

	if (this->Unload())
	{
		this->pFilename = filename;
		this->pRes = res;
		this->pPool = pool;

		SECURITY_CHECK(pFileSystem->Open(filename, &stFile, pool), "Could not open map file.");
		const u8 *ptr = static_cast<const u8 *>(stFile.GetData());
		ObjectHeader *block = NULL;
		READ_STRUCT(block, ObjectHeader, ptr);
		//SECURITY_CHECK(seed_validate_block(&stFile, block, MAP_OBJECT_MAGIC, MAP_OBJECT_VERSION), "Invalid block header for map.");

		u32 skip = 0;
		READ_U32(skip, ptr);

		READ_U32(iWidthInTiles, ptr);
		READ_U32(iHeightInTiles, ptr);
		READ_U32(ptiTileSize.x, ptr);
		READ_U32(ptiTileSize.y, ptr);
		READ_U32(iLayerCount, ptr);

#if 1
		// Para fazer o mapa encaixar exatamente no tamanho da tela em altura e largura.
		// Devemos ver como deixar essa informacao configuravel.
		ptiTileSize.x = pScreen->GetWidth() / iWidthInTiles;
		ptiTileSize.y = pScreen->GetHeight() / iHeightInTiles;
#endif

		fTileWidth = static_cast<f32>(ptiTileSize.x) / static_cast<f32>(pScreen->GetWidth());
		fTileHeight = static_cast<f32>(ptiTileSize.y) / static_cast<f32>(pScreen->GetHeight());
		iViewWidthInTiles = static_cast<u32>(ceil(this->GetWidth() * pScreen->GetWidth() / ptiTileSize.x));
		iViewHeightInTiles = static_cast<u32>(ceil(this->GetHeight() * pScreen->GetHeight() / ptiTileSize.y));
        iViewWidthInTiles = iViewWidthInTiles > iWidthInTiles ? iWidthInTiles : iViewWidthInTiles;
        iViewHeightInTiles = iViewHeightInTiles > iHeightInTiles ? iHeightInTiles : iViewHeightInTiles;

		LayerHeader *layers = (LayerHeader *)ptr;
		ptr = &ptr[sizeof(LayerHeader) * iLayerCount];

		for (u32 i = 0; i < iLayerCount; i++)
		{
			u32 layerId = 0;
			IMapLayer *layer = NULL;

			switch (layers[i].iType)
			{
				case LayerTypeTiled:
				{
					layerId = this->AddLayerTiled();
					MapLayerTiled *tiled = arLayers[layerId]->AsTiled();
					layer = tiled;
					if (tiled)
					{
						tiled->SetWrap(TRUE);
						tiled->SetTileSize(ptiTileSize);
						tiled->SetTileData(static_cast<const u32 *>((void *)&ptr[layers[i].iDataIndex]));
						tiled->Initialize(iWidthInTiles, iHeightInTiles);
						tiled->SetView(iViewWidthInTiles, iViewHeightInTiles);
					}
				}
				break;

				case LayerTypeMetadata:
				{
					layerId = this->AddLayerMetadata();
					MapLayerMetadata *data = arLayers[layerId]->AsMetadata();
					layer = data;
					if (data)
					{
						const u32 *ptru = static_cast<const u32 *>((void *)&ptr[layers[i].iDataIndex]);
						const LayerObjectHeader *ptrd = static_cast<const LayerObjectHeader *>((void *)&ptru[1]);
						data->Initialize(ptiTileSize, ptru[0], ptrd, world);
					}
				}
				break;

				case LayerTypeMosaic:
				{
					layerId = this->AddLayerMosaic();
					MapLayerMosaic *mosaic = arLayers[layerId]->AsMosaic();
					layer = mosaic;
					if (mosaic)
					{
					}
				}
				break;

				default:
				{
				}
				break;
			}

			if (layer)
			{
				layer->SetPriority(i);
				layer->SetName(Str(layers[i].iNameId));
				layer->SetOpacity(layers[i].fOpacity);
				layer->SetVisible(layers[i].iVisible > 0);
				cMapLayers.Add(layer);
			}
		}

		bLoaded = TRUE;
	}

	return bLoaded;
}

INLINE BOOL Map::Unload()
{
	stFile.Close();
	iWidthInTiles = 0;
	iHeightInTiles = 0;
	ptiTileSize.x = 0;
	ptiTileSize.y = 0;
	iLayerCount = 0;
	bLoaded = FALSE;

	return TRUE;
}

INLINE void Map::Reset()
{
	for (u32 i = 0; i < arLayers.Size(); i++)
	{
		Delete(arLayers[i]);
	}

	arLayers.Truncate();
}

INLINE void Map::Update(f32 dt)
{
	if (bTransformationChanged)
	{
		iViewWidthInTiles = static_cast<u32>(this->GetWidth() / fTileWidth);
		iViewHeightInTiles = static_cast<u32>(this->GetHeight() / fTileHeight);

		for (u32 i = 0; i < cMapLayers.Size(); i++)
		{
			cMapLayers.GetChildAt(i)->Update(dt);
		}
	}
}

INLINE void Map::Render()
{
	for (u32 i = 0; i < cMapLayers.Size(); i++)
	{
		cMapLayers.GetChildAt(i)->Render();
	}
}

INLINE u32 Map::AddLayerTiled()
{
	u32 layerId = arLayers.Size();

	MapLayerTiled *layer = New(MapLayerTiled);
	arLayers.Add(layer);
	cMapLayers.Add(layer);

	return layerId;
}

INLINE u32 Map::AddLayerMetadata()
{
	u32 layerId = arLayers.Size();

	MapLayerMetadata *layer = New(MapLayerMetadata);
	arLayers.Add(layer);
	cMapLayers.Add(layer);

	return layerId;
}

INLINE u32 Map::AddLayerMosaic()
{
	u32 layerId = arLayers.Size();

	MapLayerMosaic *layer = New(MapLayerMosaic);
	arLayers.Add(layer);
	cMapLayers.Add(layer);

	return layerId;
}

INLINE IMapLayer *Map::GetLayerAt(u32 index)
{
	return arLayers[index];
}

INLINE IMapLayer *Map::GetLayerByName(const char *name)
{
	IMapLayer *map = NULL;
	u32 len = arLayers.Size();
	for (u32 i = 0; i < len; i++)
	{
		if (STRCASECMP(arLayers[i]->GetName(), name) == 0)
		{
			map = arLayers[i];
			break;
		}
	}

	return map;
}

INLINE int Map::GetObjectType() const
{
	return Seed::ObjectMap;
}

INLINE const char *Map::GetObjectName() const
{
	return "Map";
}
