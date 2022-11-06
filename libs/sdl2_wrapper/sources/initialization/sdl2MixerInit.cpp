#include "initialization/sdl2MixerInit.h"
#include "logging/logFile.h"
#include "SDL_mixer.h"

sdl2::MixerModule::MixerModule(LogFile& log)
{
	if( -1 == Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) )
	{
		log.wrRessourceInitError("SDL2 Mixer", Mix_GetError() );
		isMixerInitialized = false;
	}
	else{
		Mix_AllocateChannels(22);
		isMixerInitialized = true;
	}
}

sdl2::MixerModule::~MixerModule()
{
	if( isMixerInitialized )
	{
		Mix_CloseAudio();
	}
}

bool sdl2::MixerModule::wasLoadingPerfect() const
{
	return isMixerInitialized;
}