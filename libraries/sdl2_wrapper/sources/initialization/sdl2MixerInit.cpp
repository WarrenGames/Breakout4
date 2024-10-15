#include "initialization/sdl2MixerInit.h"
#include "logging/logFile.h"
#include "SDL_mixer.h"

constexpr int MixerDefaultChannelsNumber = 22;

sdl2::MixerModule::MixerModule(LogFile& log):
	isMixerInitialized{true}
{
	initSdl2Mixer(log, MixerDefaultChannelsNumber);
}

sdl2::MixerModule::MixerModule(LogFile& log, int customChannelsNumber):
	isMixerInitialized{true}
{
	initSdl2Mixer(log, customChannelsNumber);
}

sdl2::MixerModule::~MixerModule()
{
	if( isMixerInitialized )
	{
		Mix_CloseAudio();
	}
}

sdl2::MixerModule::operator bool() const
{
	return isMixerInitialized;
}

bool sdl2::MixerModule::wasLoadingPerfect() const
{
	return isMixerInitialized;
}

void sdl2::MixerModule::initSdl2Mixer(LogFile& log, int customChannelsNumber)
{
	/*	Mix_OpenAudio(sound frequency here: 44100 Hertz, 
						16 bits sample type represented by 'MIX_FEAULT_FORMAT' define,
						Mono or Stereo, but MIX_DEFAULT_CHANNELS is equal to 2,
						1024 or 2048 here are reasonnable values.
		Read more infos on the official internet documentation page: 'https://wiki.libsdl.org/SDL2_mixer/Mix_OpenAudio'
	*/
	if( -1 == Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) )
	{
		log.wrRessourceInitError("SDL2 Mixer", Mix_GetError() );
		isMixerInitialized = false;
	}
	else{
		Mix_AllocateChannels(customChannelsNumber);
		isMixerInitialized = true;
	}
}