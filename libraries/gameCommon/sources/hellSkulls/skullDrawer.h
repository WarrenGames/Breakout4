#ifndef HELL_SKULL_DRAWER_H
#define HELL_SKULL_DRAWER_H

#include "advancedDrawing/texturesLoading/2dimTexturesLoading.h"
#include "advancedDrawing/texturesDrawing/2dimTexturesDrawing.h"

struct Essentials;
struct SkullData;

class HellSkullDrawer
{
private:
	Matrix2DTexturesLoading loadedTextures;
	Matrix2DTexturesDrawing drawer;

public:
	explicit HellSkullDrawer(Essentials& essentials);
	~HellSkullDrawer() = default;
	HellSkullDrawer( const HellSkullDrawer& ) = delete;
	HellSkullDrawer& operator= ( const HellSkullDrawer& ) = delete;
	HellSkullDrawer( HellSkullDrawer&& ) = default;
	HellSkullDrawer& operator= ( HellSkullDrawer&& ) = default;
	
	bool wasLoadingPerfect() const;
	void drawHellSkull(Essentials& essentials, const SkullData& hellSkullData);
	int getTextureWidth(const SkullData& hellSkullData) const;
	int getTextureHeight(const SkullData& hellSkullData) const;
};

#endif //HELL_SKULL_DRAWER_H