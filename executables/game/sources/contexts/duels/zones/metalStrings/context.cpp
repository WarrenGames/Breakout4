#include "contexts/duels/zones/metalStrings/context.h"
#include "types/essentialsStruct.h"
#include "text/sdl2ttf_font.h"
#include "contexts/duels/inGameObjects/gameElements/duelsTypes.h"
#include "contexts/duels/zones/metalStrings/subObjects/globalSpecificObject.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"

void duels::strings::context(Essentials& essentials, unsigned finalScore, duels::LevelOptions& levelOptions)
{
	if( const sdl2::Font arial{essentials.logs.error, ArialFontPath, FontBigPointSize} )
	{
		if( duels::MetalStrings global{essentials, arial, levelOptions} )
		{
			duels::strings::mainLoop(essentials, finalScore, levelOptions, arial, global);
		}
	}
}

void duels::strings::mainLoop(Essentials& essentials, unsigned finalScore, duels::LevelOptions& levelOptions, const sdl2::Font& arial, duels::MetalStrings& global)
{
	bool quitZone{false};
	while( false == quitZone )
	{
		global.update(essentials, arial, levelOptions, quitZone);
		duels::strings::drawEverything(essentials, global);
		levelOptions.setChampionshipEnd(finalScore, quitZone);
	}
}

void duels::strings::drawEverything(Essentials& essentials, duels::MetalStrings& global)
{
	if( essentials.drawFreq.canDrawGame() )
	{
		essentials.rndWnd.clearScreen(BlackColor);
		global.drawEverything(essentials);
		essentials.rndWnd.displayRenderer();
	}
}
