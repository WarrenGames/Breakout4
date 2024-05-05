#ifndef COMMON_FILES_LIB_GAME_SOUND_SYSTEM_H
#define COMMON_FILES_LIB_GAME_SOUND_SYSTEM_H

#include "generic/gameSoundSystem/soundsFileDataPaths.h"
#include "soundSystem/soundSystem.h"

struct AppLogFiles;
class PrefPathFinder;

struct GameSoundSystem
{
	SoundSystemFilesPaths soundSystemFilesPaths;
	SoundSystem soundSystem;
	
	explicit GameSoundSystem(AppLogFiles& logs, const PrefPathFinder& prefPath, const fs::path& soundsFileList, const fs::path& groupTagCfg, 
								unsigned expectedSoundsNumber, unsigned expectedGroupTagsNumber);
	~GameSoundSystem() = default;
	GameSoundSystem( const GameSoundSystem& ) = delete;
	GameSoundSystem& operator= ( const GameSoundSystem& ) = delete;
	GameSoundSystem( GameSoundSystem&& ) = default;
	GameSoundSystem& operator= ( GameSoundSystem&& ) = default;
};

#endif //COMMON_FILES_LIB_GAME_SOUND_SYSTEM_H