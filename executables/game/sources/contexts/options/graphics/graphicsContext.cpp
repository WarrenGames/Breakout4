#include "contexts/options/graphics/graphicsContext.h"
#include "types/essentialsStruct.h"
#include "contexts/options/graphics/graphicsMenuData.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void optionsMenu::graphics::graphicsContext(Essentials& essentials)
{
	GraphicsData graphicsData{essentials};
	bool quitMenu{false};
	optionsMenu::graphics::mainLoop(essentials, graphicsData, quitMenu);
	graphicsData.writeDataToFiles(essentials);
	essentials.drawFreq.changeFramesPerSecond(graphicsData.getFramePerSecond() );
}

void optionsMenu::graphics::mainLoop(Essentials& essentials, optionsMenu::GraphicsData& graphicsData, bool& quitMenu)
{
	while( false == quitMenu )
	{
		essentials.inp.updateEvents();
		optionsMenu::graphics::quitGraphicsMenu(essentials, quitMenu);
		optionsMenu::graphics::quitWithButton(graphicsData, quitMenu);
		optionsMenu::graphics::update(essentials, graphicsData);
		optionsMenu::graphics::drawEverything(essentials, graphicsData);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void optionsMenu::graphics::update(Essentials& essentials, optionsMenu::GraphicsData& graphicsData)
{
	graphicsData.updateBox(essentials);
}

void optionsMenu::graphics::drawEverything(Essentials& essentials, optionsMenu::GraphicsData& graphicsData)
{
	graphicsData.drawEverything(essentials);
	essentials.rndWnd.displayRenderer();
	SDL_Delay(SdlDelayTime);
}

void optionsMenu::graphics::quitGraphicsMenu(Essentials& essentials, bool& quitMenu)
{
	if( essentials.inp.getKeyState(input::KeybOut) || essentials.inp.getSDL_quit() )
	{
		quitMenu = true;
		essentials.inp.setKeyStateToFalse(input::KeybOut);
	}
}

void optionsMenu::graphics::quitWithButton(optionsMenu::GraphicsData& graphicsData, bool& quitMenu)
{
	if( graphicsData.quitButtonClicked() )
	{
		quitMenu = true;
	}
}