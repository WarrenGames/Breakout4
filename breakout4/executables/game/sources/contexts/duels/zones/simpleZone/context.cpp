#include "contexts/duels/zones/simpleZone/context.h"
#include "types/essentialsStruct.h"
#include "text/sdl2ttf_font.h"
#include "consts/fontsConsts.h"
#include "contexts/duels/inGameObjects/gameElements/duelsTypes.h"
#include "contexts/duels/inGameObjects/global/duelsGlobalObject.h"
#include "contexts/duels/zones/simpleZone/simpleZoneArea.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"

void duels::simple::context(Essentials& essentials, unsigned finalScore, duels::LevelOptions& levelOptions)
{
	if( const sdl2::Font arial{essentials.logs.error, ARIALFONTPATH, FONT_BIG_PTSIZE} )
	{
		duels::SimpleZone simpleZone{essentials.logs, essentials.rndWnd, arial, levelOptions.pointsToPlayInZone};
		duels::GlobalObject global{essentials, arial, simpleZone.ballsAndCoinsSpawn, levelOptions};
		
		if( global.wasLoadingPerfect() && simpleZone.isLoadingPerfect )
		{
			duels::simple::mainLoop(essentials, arial, global, finalScore, levelOptions, simpleZone);
		}
	}
}

void duels::simple::mainLoop(Essentials& essentials, const sdl2::Font& arial, duels::GlobalObject& global, unsigned finalScore, duels::LevelOptions& levelOptions, duels::SimpleZone& simpleZone)
{
	bool quitZone{false};
	while( false == quitZone )
	{
		global.update(simpleZone.levelGrid, levelOptions, quitZone, {true, true}, {true, true}, {false, false});
		global.resetScoresTextures(essentials.logs, essentials.rndWnd, arial, levelOptions);
		duels::simple::drawEverything(essentials, global, simpleZone);
		levelOptions.setChampionshipEnd(finalScore, quitZone);
	}
}

void duels::simple::drawEverything(Essentials& essentials, duels::GlobalObject& global, duels::SimpleZone& simpleZone)
{
	if( essentials.drawFreq.canDrawGame() )
	{
		essentials.rndWnd.clearScreen(BLACK_COL);
		simpleZone.drawZone(essentials.rndWnd);
		global.drawEverything(essentials.rndWnd);
		essentials.rndWnd.displayRenderer();
	}
}