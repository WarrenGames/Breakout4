#include "initialization/sdl2ModuleInit.h"
#include "logging/logFile.h"
#include "SDL.h"

sdl2::ModuleInit::ModuleInit(Uint32 flags, LogFile& log)
{
	if( SDL_Init( flags ) != 0 )
	{
		log.wrRessourceInitError("SDL2 initialization", SDL_GetError() );
		isSDL2initialized = false;
	}
	else{
		SDL_JoystickEventState(SDL_ENABLE);
		isSDL2initialized = true;
	}
}

sdl2::ModuleInit::~ModuleInit()
{
	if( isSDL2initialized )
		SDL_Quit();
}

bool sdl2::ModuleInit::wasLoadingPerfect() const
{
	return isSDL2initialized;
}