#include "options/joystickInterface/joystickInfosInterface.h"
#include "options/joystickInterface/joystickGraphicsValues.h"
#include "types/essentialsStruct.h"
#include "texts/textLoader.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/optionsLanguageConsts.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"
#include "SDL_timer.h"

void joyCfg::mainContext(Essentials& essentials, const sdl2::Font& arial, const sdl2::JoystickEntity& joyEnt)
{
	const TextsBlocks joystickTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::OptionMenuJoystickDetails), 15};
	JoystickValuesTextures joyTextures{essentials.logs, essentials.rndWnd, arial, joystickTexts, joyEnt};
	
	joyCfg::mainLoop(essentials, joyTextures);
}

void joyCfg::mainLoop(Essentials& essentials, JoystickValuesTextures& joystickTextures)
{
	while( false == joystickTextures.isQuitTriggered() )
	{
		joystickTextures.updateEvents();
		essentials.rndWnd.clearScreen(SDL_Color{192, 192, 192, 255});
		joystickTextures.drawAll(essentials.rndWnd);
		essentials.rndWnd.displayRenderer();
		SDL_Delay(SdlDelayTime);
	}
}
