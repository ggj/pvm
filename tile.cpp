#include "tile.h"

Tile::Tile()
	: iType(0)
{
}

Tile::~Tile()
{
}

u32 Tile::GetType() const
{
	return iType;
}

void Tile::SetType(u32 type)
{
	iType = type;
}

void *Tile::operator new(size_t len)
{
	return pMemoryManager->Alloc(len, pDefaultPool, "operator new", "Tile" "Tile");
}

void Tile::operator delete(void *ptr)
{
	pMemoryManager->Free(ptr, pDefaultPool);
}

void *Tile::operator new[](size_t) throw()
{
	return NULL;
}

void Tile::operator delete[](void *)
{
}

/**/

TileSprite::TileSprite()
	: pTile(NULL)
{
}

TileSprite::~TileSprite()
{
}

void TileSprite::SetTile(const Tile *tile)
{
	pTile = tile;
	this->SetAnimation(tile->GetType());
}

