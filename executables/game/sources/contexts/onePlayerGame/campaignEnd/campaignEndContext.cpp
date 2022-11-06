#include "contexts/onePlayerGame/campaignEnd/campaignEndContext.h"
#include "contexts/onePlayerGame/campaignEnd/campEndInterface.h"
#include "crossLevel/playerData.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void onePlGame::campaignEnd::context(Essentials& essentials, const PlayerData& playerData)
{
	bool quit{false};
	const onePlGame::campaignEnd::Interface interface{essentials, playerData};
	while( false == quit )
	{
		essentials.inp.updateEvents();
		onePlGame::campaignEnd::waitForUserInput(essentials, quit);
		onePlGame::campaignEnd::drawEverything(essentials, interface);
	}
}

void onePlGame::campaignEnd::waitForUserInput(Essentials& essentials, bool& quitMenu)
{
	if( essentials.inp.getKeyState(input::KeybOut) || essentials.inp.getSDL_quit() )
	{
		essentials.inp.setKeyStateToFalse(input::KeybOut);
		quitMenu = true;
	}
}

void onePlGame::campaignEnd::drawEverything(Essentials& essentials, const onePlGame::campaignEnd::Interface& interface)
{
	essentials.rndWnd.clearScreen(BlackColor);
	interface.drawEverything(essentials);
	essentials.rndWnd.displayRenderer();
	SDL_Delay(SdlDelayTime);
}