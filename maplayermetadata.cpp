#include "maplayermetadata.h"
#include "imetadataobject.h"
#include "collisionobject.h"
#include "triggerobject.h"
#include "spawnerobject.h"

MapLayerMetadata::MapLayerMetadata()
	: arObjects()
	, iObjects(0)
	, ptiTileSize(0, 0)
{
	arObjects.Truncate();
	cScene.SetParent(this);
}

MapLayerMetadata::~MapLayerMetadata()
{
	this->Reset();
}

void MapLayerMetadata::Reset()
{
	for (u32 i = 0; i < iObjects; i++)
	{
		Delete(arObjects[i]);
	}

	arObjects.Truncate();
	iObjects = 0;

	cScene.Reset();
}

void MapLayerMetadata::Initialize(Point2u tileSize, u32 count, const LayerObjectHeader *data, b2World *world)
{
	ptiTileSize = tileSize;
	iObjects = count;
	for (u32 i = 0; i < iObjects; i++)
	{
		arObjects.Add(this->CreateObject(&data[i], world));
	}
}

IMetadataObject *MapLayerMetadata::CreateObject(const LayerObjectHeader *entry, b2World *world)
{
	const char *type = Str(entry->iTypeId);
	IMetadataObject *obj = NULL;

	bool physics = false;
	if (STRCMP(type, "trigger") == 0)
	{
		obj = New(TriggerObject());
	}
	else if (STRCMP(type, "spawner") == 0)
	{
		obj = New(SpawnerObject());
	}
	else
	{
		obj = New(CollisionObject(world));
		physics = true;
	}

	obj->SetNameId(entry->iNameId);
	obj->SetTypeId(entry->iTypeId);
	obj->LoadProperties(entry->iPropertiesId);
	obj->SetPosition(entry->fPosX * ptiTileSize.x, entry->fPosY * ptiTileSize.y);
	obj->SetWidth(entry->fWidth * ptiTileSize.x);
	obj->SetHeight(entry->fHeight * ptiTileSize.y);

	if (physics)
	{
		((CollisionObject*)obj)->CreateStaticBody(obj->GetX(), obj->GetY() + obj->GetHeight(), obj->GetWidth(), obj->GetHeight());
	}

	cScene.Add(obj);

	return obj;
}

Point2i MapLayerMetadata::ViewAt(Point2i pos)
{
	cScene.SetPosition(-pos.x / static_cast<f32>(pScreen->GetWidth()), -pos.y / static_cast<f32>(pScreen->GetHeight()));

	return pos;
}

BOOL MapLayerMetadata::CheckHit(const Rect4f &area, CollisionDataArrayPtr col) const
{
	BOOL result = FALSE;
	for (u32 i = 0; i < iObjects; i++)
	{
		IMetadataObject *obj = arObjects.At(i);
		Rect4f overlap;
		if (obj->CheckHit(area, overlap))
		{
			col->Add();

			CollisionData *data = &(*col)[col->Size() - 1];
			data->obj = obj;
			data->overlap = overlap;

			result = TRUE;
		}
	}

	return result;
}

void MapLayerMetadata::Update(f32 dt)
{
	cScene.Update(dt);
}

void MapLayerMetadata::Render()
{
	for (u32 i = 0; i < iObjects; i++)
	{
		IMetadataObject *obj = arObjects[i];
		obj->Render();
	}
}

MapLayerMetadata *MapLayerMetadata::AsMetadata()
{
	return this;
}
