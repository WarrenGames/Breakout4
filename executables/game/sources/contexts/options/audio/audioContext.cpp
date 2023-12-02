#include "contexts/options/audio/audioContext.h"
#include "contexts/options/audio/audioPanel.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void audioOptions::mainContext(Essentials& essentials)
{
	bool quitMenu{false};
	AudioPanelGraphics panel{essentials};
	audioOptions::mainLoop(essentials, panel, quitMenu);
	panel.writeDataToFile(essentials);
}

void audioOptions::mainLoop(Essentials& essentials, AudioPanelGraphics& panel, bool& quitMenu)
{
	while( false == quitMenu )
	{
		essentials.inp.updateEvents();
		audioOptions::quitMenu(essentials, quitMenu);
		panel.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
		panel.updateWithButtons();
		audioOptions::drawEverything(essentials, panel);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void audioOptions::drawEverything(Essentials& essentials, const AudioPanelGraphics& panel)
{
	essentials.rndWnd.clearScreen(BlackColor);
	panel.drawAll(essentials.rndWnd);
	essentials.rndWnd.displayRenderer();
	SDL_Delay(SdlDelayTime);
}

void audioOptions::quitMenu(Essentials& essentials, bool& quitMenu)
{
	if( essentials.inp.getSDL_quit() || essentials.inp.getKeyState(input::KeybOut) )
	{
		quitMenu = true;
		essentials.inp.setKeyStateToFalse(input::KeybOut);
	}
}