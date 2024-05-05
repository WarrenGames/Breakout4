#include "sounds/loadSound.h"
#include "logging/logFile.h"

Mix_Chunk* loadSoundChunk(LogFile& log, const fs::path& soundPath)
{
	Mix_Chunk *sound = Mix_LoadWAV( soundPath.string().c_str() );
	if( sound )
	{
		return sound;
	}
	else
	{
		log.wrRessourceCreationError("Mix_Chunk pointer", Mix_GetError() );
		return nullptr;
	}
}

Mix_Music* loadMixMusic(LogFile& log, const fs::path& musicPath)
{
	Mix_Music *music = Mix_LoadMUS( musicPath.string().c_str() );

	if( music )
		return music;
	else{
		log.wrRessourceCreationError("Mix_Music pointer", Mix_GetError() );
		return nullptr;
	}
}
