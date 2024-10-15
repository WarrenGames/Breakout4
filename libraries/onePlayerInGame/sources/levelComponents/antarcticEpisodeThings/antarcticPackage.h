#ifndef ONE_PLAYER_ANTARCTIC_PACKAGE_H
#define ONE_PLAYER_ANTARCTIC_PACKAGE_H

#include "stalactites/stalactitesDrawer.h"
#include "rectCollisions/rectLoader.h"
#include "levelComponents/antarcticEpisodeThings/stalactites/onePlayerStalactitesLoading.h"
#include "levelComponents/antarcticEpisodeThings/stalactites/iceStalactites.h"
#include "advancedDrawing/texturesLoading/2dimTexturesLoading.h"
#include "advancedDrawing/texturesDrawing/2dimTexturesDrawing.h"
#include "levelComponents/antarcticEpisodeThings/onePlayerPinguins/pinguinsDataLoader.h"
#include "levelComponents/antarcticEpisodeThings/onePlayerPinguins/onePlayerPinguin.h"
#include "levelComponents/demosObjects/antarcticDemoPackage.h"

struct Essentials;

struct AntarcticPackage
{
	StalactitesDrawer stalactitesDrawer;
	RectLoader stalactitesRects;
	onePlGame::StalactitesLoading stalactitesDataLoading;
	IceStalactitesElements stalactitesData;
	
	Matrix2DTexturesLoading pinguinTextures;
	Matrix2DTexturesDrawing pinguinSprites;
	onePlGame::PinguinsDataLoader pinguinsDataLoader;
	OnePlayerPinguin pinguinsData;
	demos::DemoAntarcticPackage antarcticDemoPackage;
	
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