#include "contexts/onePlayerGame/seeNextLevel/context.h"
#include "contexts/onePlayerGame/levelComponents/global/globalGameObject.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"

void seeLevel::context(Essentials& essentials, const PlayerData& playerData)
{
	if( LevelComponents levelComponents{essentials, playerData, 0} )
	{
		bool quitLevelSketch{false};
		while( false == quitLevelSketch )
		{
			essentials.inp.updateEvents();
			seeLevel::quitContext(essentials, quitLevelSketch);
			levelComponents.levelSketch(essentials);
			essentials.rndWnd.displayRenderer();
			SDL_Delay(SDL_DELAY_TIME);
		}
	}
}

void seeLevel::quitContext(Essentials& essentials, bool& quitLevelSketch)
{
	if( essentials.inp.getSDL_quit() || essentials.inp.getKeyState(input::KEYB_OUT) )
	{
		quitLevelSketch = true;
		essentials.inp.setKeyStateToFalse(input::KEYB_OUT);
	}
}