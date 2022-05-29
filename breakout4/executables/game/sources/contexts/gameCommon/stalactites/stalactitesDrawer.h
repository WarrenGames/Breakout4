#ifndef STALACTITES_DRAWER_H
#define STALACTITES_DRAWER_H

#include "advancedDrawing/texturesLoading/fileTexturesList.h"
#include "advancedDrawing/texturesDrawing/constAnimationDrawing.h"

struct Essentials;
class StalactiteData;

class StalactitesDrawer
{
private:
	TexturesFilesList loadedTextures;
	ConstAnimDraw sprites;
	bool isLoadingPerfect;
	
public:
	explicit StalactitesDrawer(Essentials& essentials);
	~StalactitesDrawer() = default;
	StalactitesDrawer( const StalactitesDrawer& ) = delete;
	StalactitesDrawer& operator= ( const StalactitesDrawer& ) = delete;
	StalactitesDrawer( StalactitesDrawer&& ) = default;
	StalactitesDrawer& operator= ( StalactitesDrawer&& ) = default;
	
	void drawStalactite(Essentials& essentials, const StalactiteData& stalactite);
	bool wasLoadingPerfect() const;
	int getWidth(unsigned stalactiteDirection) const;
	int getHeight(unsigned stalactiteDirection) const;
};




#endif //STALACTITES_DRAWER_H