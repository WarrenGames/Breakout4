#include "initialization/sdl2TTF_Init.h"
#include "SDL_ttf.h"
#include "logging/logFile.h"

sdl2::TTFModule::TTFModule(LogFile& log)
{
	if( TTF_Init() == -1 )
	{
		log.wrRessourceInitError("SDL TTF initialization", TTF_GetError() );
		isTTFinitialized = false;
	}
	else
		isTTFinitialized = true;
}

sdl2::TTFModule::~TTFModule()
{
	if( isTTFinitialized )
		TTF_Quit();
}

bool sdl2::TTFModule::wasLoadingPerfect() const
{
	return isTTFinitialized;
}