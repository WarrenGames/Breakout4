#include "contexts/duels/zones/halloween/subObjects/halloweenGlobalObject.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "consts/sdlColors.h"

duels::HalloweenPack::HalloweenPack(Essentials& essentials, const duels::LevelOptions& levelOptions):
	arial{essentials.logs.error, ArialFontPath, FontBigPointSize},
	factory{essentials, levelOptions.halloween},
	area{essentials, arial, levelOptions.pointsToPlayInZone},
	zonesCommon{essentials, arial, area.ballsAndCoinsSpawn, levelOptions},
	nightWallpaper{essentials.logs, essentials.rndWnd, "textures/wallpapers/halloweenHouseNightTime.png", TexturePosition{0, 0} },
	daytimeWallpaper{essentials.logs, essentials.rndWnd, "textures/wallpapers/halloweenHouseDaytime.png", TexturePosition{0, 0} }
{
	
}

bool duels::HalloweenPack::wasLoadingPerfect() const
{
	return arial && area.isLoadingPerfect && zonesCommon.wasLoadingPerfect();
}

void duels::HalloweenPack::update(Essentials& essentials, duels::LevelOptions& levelOptions, bool& quitZone)
{
	zonesCommon.update(area.levelGrid, levelOptions, quitZone, {true, true}, {true, true}, {factory.canActivateSpecialBonus(duels::PlayerBlue), 
																							factory.canActivateSpecialBonus(duels::PlayerRed)} );
	factory.update(levelOptions, zonesCommon);
	zonesCommon.resetScoresTextures(essentials.logs, essentials.rndWnd, arial, levelOptions);
	activateSpecificFlagIfAny(levelOptions);
}

void duels::HalloweenPack::drawWallpaper(Essentials& essentials, const duels::LevelOptions& levelOptions) const
{
	if( levelOptions.halloween.canDisplayWallpaper )
	{
		if( levelOptions.halloween.wallpaperIsDaytime )
		{
			daytimeWallpaper.draw(essentials.rndWnd);
		}
		else{
			nightWallpaper.draw(essentials.rndWnd);
		}
	}
}

void duels::HalloweenPack::drawEverything(Essentials& essentials, const duels::LevelOptions& levelOptions)
{
	if( essentials.drawFreq.canDrawGame() )
	{
		essentials.rndWnd.clearScreen(BlackColor);
		drawWallpaper(essentials, levelOptions);
		area.drawZone(essentials.rndWnd);
		area.drawMushrooms(essentials.rndWnd, levelOptions);
		zonesCommon.drawEverything(essentials.rndWnd);
		factory.drawEverything(essentials);
		essentials.rndWnd.displayRenderer();
	}
}

void duels::HalloweenPack::activateSpecificFlagIfAny(const duels::LevelOptions& levelOptions)
{
	for( unsigned playerNum{0} ; playerNum < duels::PlayerMax ; ++playerNum )
	{
		if( zonesCommon.canConsumeZoneSpecificFlag(playerNum) )
		{
			factory.activateSpecialBonus(levelOptions, playerNum);
		}
	}
}