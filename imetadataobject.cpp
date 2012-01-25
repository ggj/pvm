#include "imetadataobject.h"

IMetadataObject::IMetadataObject()
	: pcName(NULL)
	, pcType(NULL)
	, pcProperties(NULL)
	, cArea()
	, iNameId(0)
	, iTypeId(0)
{
}

IMetadataObject::~IMetadataObject()
{
}

void IMetadataObject::SetPosition(f32 x, f32 y)
{
	ITransformable2D::SetPosition(x / static_cast<f32>(pScreen->GetWidth()), y / static_cast<f32>(pScreen->GetHeight()));
	cArea.x = x;
	cArea.y = y;
}

void IMetadataObject::SetWidth(f32 w)
{
	ITransformable2D::SetWidth(w / static_cast<f32>(pScreen->GetWidth()));
	cArea.width = w;
}

void IMetadataObject::SetHeight(f32 h)
{
	ITransformable2D::SetHeight(h / static_cast<f32>(pScreen->GetHeight()));
	cArea.height = h;
}

const Rect4f &IMetadataObject::GetBoundingBox() const
{
	return cArea;
}

BOOL IMetadataObject::CheckHit(const Rect4f &area, Rect4f &overlap) const
{
	return area.GetOverlappedRect(cArea, overlap);
}

void IMetadataObject::SetNameId(u32 nameId)
{
	iNameId = nameId;
	pcName = Str(nameId);
}

u32 IMetadataObject::GetNameId() const
{
	return iNameId;
}

const char *IMetadataObject::GetName() const
{
	return pcName;
}

void IMetadataObject::SetTypeId(u32 typeId)
{
	iTypeId = typeId;
	pcType = Str(typeId);
}

u32 IMetadataObject::GetTypeId() const
{
	return iTypeId;
}

const char *IMetadataObject::GetType() const
{
	return pcType;
}

void IMetadataObject::LoadProperties(u32 propId)
{
	pcProperties = Str(propId);
}

const char *IMetadataObject::GetProperties() const
{
	return pcProperties;
}
