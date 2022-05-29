#include "contexts/gameStarting/sdlLogoDisplay/logoDispContext.h"
#include "contexts/gameStarting/sdlLogoDisplay/sdlVersionDisplay.h"
#include "texturing/texturesCombo.h"
#include "texturing/texturePosition.h"
#include "time/accurateTime.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void logoDisplay::mainContext(Essentials& essentials)
{
	const TextureCombo sdlLogo{essentials.logs, essentials.rndWnd, "textures/gameGUI/sdlLogo/sdlLogo1280.png", TexturePosition{GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2, true, true} };
	AccurateTimeDelay displayDelay;
	const SDL_VersionDisplay versionDisplay{essentials};
	bool quitLogoDisplay{false};
	while( false == quitLogoDisplay )
	{
		logoDisplay::loopThings(essentials, quitLogoDisplay, sdlLogo, versionDisplay, displayDelay);
	}
}

void logoDisplay::loopThings(Essentials& essentials, bool& quitLogoDisplay, const TextureCombo& sdlLogo, const SDL_VersionDisplay& versionDisplay, AccurateTimeDelay& displayDelay)
{
	logoDisplay::waitForKeyToBePushed(quitLogoDisplay);
	logoDisplay::quitIfTimeElapsed(quitLogoDisplay, displayDelay);
	essentials.rndWnd.clearScreen(BLACK_COL);
	sdlLogo.draw(essentials.rndWnd);
	versionDisplay.drawVersion(essentials);
	essentials.rndWnd.displayRenderer();
	SDL_Delay(SDL_DELAY_TIME);
}

void logoDisplay::waitForKeyToBePushed(bool& quitLogoDisplay)
{
	SDL_Event events;
	while( SDL_PollEvent(&events) )
	{
		switch( events.type )
		{
			case SDL_KEYDOWN:
				quitLogoDisplay = true;
				break;
		}
	}
}

void logoDisplay::quitIfTimeElapsed(bool& quitLogoDisplay, AccurateTimeDelay& displayDelay)
{
	if( displayDelay.hasTimeElapsed( std::chrono::milliseconds{4000} ) )
	{
		quitLogoDisplay = true;
	}
}