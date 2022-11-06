#include "contexts/options/joystickInterface/joystickInfosInterface.h"
#include "contexts/options/joystickInterface/joystickGraphicsValues.h"
#include "types/essentialsStruct.h"
#include "texts/textLoader.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "contexts/options/optionsLanguageConsts.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"

void joyCfg::mainContext(Essentials& essentials, const sdl2::Font& arial, const sdl2::JoystickEntity& joyEnt)
{
	const TextsBlocks joystickTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::OPT_MENU_JOY_DETAILS), 15};
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
