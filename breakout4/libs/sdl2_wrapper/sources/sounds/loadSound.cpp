#include "sounds/loadSound.h"
#include "logging/logFile.h"

Mix_Chunk* loadSoundChunk(LogFile& log, const std::string& soundPath)
{
	Mix_Chunk *Sound = Mix_LoadWAV( soundPath.c_str() );
	if( Sound )
	{
		return Sound;
	}
	else
	{
		log.wrRessourceCreationError("Mix_Chunk pointer", Mix_GetError() );
		return nullptr;
	}
}

Mix_Music* loadMixMusic(LogFile& log, const std::string& musicPath)
{
	Mix_Music *Music = Mix_LoadMUS( musicPath.c_str() );

	if( Music )
		return Music;
	else{
		log.wrRessourceCreationError("Mix_Music pointer", Mix_GetError() );
		return nullptr;
	}
}
