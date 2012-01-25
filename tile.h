#ifndef __TILE_H__
#define __TILE_H__

#include "main.h"

class Tile
{
	public:
		Tile();
		~Tile();

		u32 GetType() const;
		void SetType(u32 type);

		void *operator new(size_t len);
		void operator delete(void *ptr);
		void *operator new[](size_t) throw();
		void operator delete[](void *);

	private:
		u32 iType;
};

class TileSprite : public SpriteInstantiable
{
	public:
		TileSprite();
		virtual ~TileSprite();

		void SetTile(const Tile *tile);

	private:
		const Tile *pTile;
};

#endif // __TILE_H__
