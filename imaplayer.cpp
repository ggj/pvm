#include "imaplayer.h"

IMapLayer::IMapLayer()
	: pcName(NULL)
	, fOpacity(1.0f)
	, bVisible(TRUE)
{
}

IMapLayer::~IMapLayer()
{
}

MapLayerTiled *IMapLayer::AsTiled()
{
	return NULL;
}

MapLayerMosaic *IMapLayer::AsMosaic()
{
	return NULL;
}

MapLayerMetadata *IMapLayer::AsMetadata()
{
	return NULL;
}

void IMapLayer::SetName(const char *name)
{
	pcName = name;
}

const char *IMapLayer::GetName() const
{
	return pcName;
}

void IMapLayer::SetVisible(BOOL b)
{
	bVisible = b;
}

BOOL IMapLayer::IsVisible() const
{
	return bVisible;
}

void IMapLayer::SetOpacity(f32 opacity)
{
	fOpacity = opacity;
}

f32 IMapLayer::GetOpacity() const
{
	return fOpacity;
}

void *IMapLayer::operator new(size_t len)
{
	return pMemoryManager->Alloc(len, pDefaultPool, "operator new", "Tile" "Tile");
}

void IMapLayer::operator delete(void *ptr)
{
	pMemoryManager->Free(ptr, pDefaultPool);
}

void *IMapLayer::operator new[](size_t) throw()
{
	return NULL;
}

void IMapLayer::operator delete[](void *)
{
}
