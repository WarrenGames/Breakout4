#include "contexts/gameStarting/initSDL2/sdl2_initialization.h"
#include "logging/logsStruct.h"
#include "initialization/sdl2ModuleInit.h"
#include "initialization/sdl2TTF_Init.h"
#include "initialization/sdl2MixerInit.h"
#include "contexts/gameStarting/setupFiles/setupConfigFiles.h"
#include "SDL.h"
#include <cassert>

void loadSDL2_modules(AppLogFiles& logs, const PrefPathFinder& prefPath)
{
	const sdl2::ModuleInit sdl2Module{SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC, logs.error};
	const sdl2::TTFModule ttfModule{logs.error};
	const sdl2::MixerModule mixerModule{logs.error};

	checkEverythingWasInit(logs, prefPath, sdl2Module, ttfModule, mixerModule);
}

void checkEverythingWasInit(AppLogFiles& logs, const PrefPathFinder& prefPath, const sdl2::ModuleInit& sdl2Module, const sdl2::TTFModule& ttfModule, const sdl2::MixerModule& mixerInit)
{
	if( sdl2Module.wasLoadingPerfect() && ttfModule.wasLoadingPerfect() && mixerInit.wasLoadingPerfect() )
	{
		setupFiles::copyConfigFilesDirectory(logs, prefPath);
	}
}
