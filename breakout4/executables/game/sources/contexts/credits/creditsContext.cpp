#include "contexts/credits/creditsContext.h"
#include "contexts/credits/creditsMenuData.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void creditsMenu::context(Essentials& essentials)
{
	creditsMenu::GraphicsData graphicsData{essentials};
	bool quitMenu{false};
	creditsMenu::mainLoop(essentials, graphicsData, quitMenu);
}

void creditsMenu::mainLoop(Essentials& essentials, const creditsMenu::GraphicsData& graphicsData, bool& quitMenu)
{
	while( false == quitMenu )
	{
		essentials.inp.updateEvents();
		creditsMenu::quitMenu(essentials, quitMenu);
		creditsMenu::drawEverything(essentials, graphicsData);
	}
}

void creditsMenu::quitMenu(Essentials& essentials, bool& quitMenu)
{
	if( essentials.inp.getSDL_quit() || essentials.inp.getKeyState(input::KEYB_OUT) )
	{
		quitMenu = true;
		essentials.inp.setKeyStateToFalse(input::KEYB_OUT);
	}
}

void creditsMenu::drawEverything(Essentials& essentials, const creditsMenu::GraphicsData& graphicsData)
{
	essentials.rndWnd.clearScreen(BLACK_COL);
	graphicsData.drawEverything(essentials);
	essentials.rndWnd.displayRenderer();
	SDL_Delay(SDL_DELAY_TIME);
}