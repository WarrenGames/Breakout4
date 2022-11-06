#ifndef ONE_PLAYER_ANTARCTIC_PACKAGE_H
#define ONE_PLAYER_ANTARCTIC_PACKAGE_H

#include "contexts/gameCommon/stalactites/stalactitesDrawer.h"
#include "contexts/gameCommon/rectCollisions/rectLoader.h"
#include "contexts/onePlayerGame/levelComponents/antarcticEpisodeThings/stalactites/iceStalactites.h"
#include "advancedDrawing/texturesLoading/2dimTexturesLoading.h"
#include "advancedDrawing/texturesDrawing/2dimTexturesDrawing.h"
#include "contexts/onePlayerGame/levelComponents/antarcticEpisodeThings/onePlayerPinguins/onePlayerPinguin.h"

struct Essentials;

struct AntarcticPackage
{
	StalactitesDrawer stalactitesDrawer;
	RectLoader stalactitesRects;
	IceStalactitesElements stalactitesData;
	
	Matrix2DTexturesLoading pinguinTextures;
	Matrix2DTexturesDrawing pinguinSprites;
	OnePlayerPinguin pinguinsData;
	
	explicit AntarcticPackage(Essentials& essentials, const PlayerData& playerData);
	~AntarcticPackage() = default;
	AntarcticPackage( const AntarcticPackage& ) = delete;
	AntarcticPackage& operator= ( const AntarcticPackage& ) = delete;
	AntarcticPackage( AntarcticPackage&& ) = default;
	AntarcticPackage& operator= ( AntarcticPackage&& ) = default;
	
	operator bool() const;
	
	void drawStalactites(Essentials& essentials);
	void drawPinguins(Essentials& essentials);
};

#endif //ONE_PLAYER_ANTARCTIC_PACKAGE_H