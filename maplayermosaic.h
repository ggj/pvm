#ifndef __MAPLAYERMOSAIC_H__
#define __MAPLAYERMOSAIC_H__

#include "imaplayer.h"

class MapLayerMosaic : public IMapLayer
{
	public:
		MapLayerMosaic();
		virtual ~MapLayerMosaic();

		MapLayerMosaic *AsMosaic();
};

#endif // __MAPLAYERMOSAIC_H__
