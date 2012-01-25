#ifndef __IMAPLAYER_H__
#define __IMAPLAYER_H__

#include "main.h"

class MapLayerTiled;
class MapLayerMosaic;
class MapLayerMetadata;

class IMapLayer : public ISceneObject
{
	public:
		IMapLayer();
		virtual ~IMapLayer();

		virtual void SetName(const char *name);
		virtual const char *GetName() const;

		virtual void SetVisible(BOOL b);
		virtual BOOL IsVisible() const;

		virtual void SetOpacity(f32 opacity);
		virtual f32 GetOpacity() const;

		virtual MapLayerTiled *AsTiled();
		virtual MapLayerMosaic *AsMosaic();
		virtual MapLayerMetadata *AsMetadata();

		void *operator new(size_t len);
		void operator delete(void *ptr);
		void *operator new[](size_t) throw();
		void operator delete[](void *);

	private:
		const char *pcName;

		f32 fOpacity;
		BOOL bVisible;
};


#endif // __IMAPLAYER_H__
