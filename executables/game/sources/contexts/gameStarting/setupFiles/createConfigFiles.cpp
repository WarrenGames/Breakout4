#include "contexts/gameStarting/setupFiles/createConfigFiles.h"
#include "prefPath/prefPathFinder.h"
#include "logging/logFile.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "fileSystem/createNewElementFs.h"
#include "consts/constexprScreen.h"
#include "consts/onePlayerLevelConsts.h"
#include "SDL_mixer.h"

void cfgFiles::createDrawFrequencyFile(LogFile& log, const PrefPathFinder& prefPath)
{
	if( prefPath.isAValidPathFound() )
	{
		if( createFs::FsNewCreated == createFs::mkNewFileIfMissing(path::getConfigDirFile(prefPath, file::DRAW_FREQ_FILE) ) )
		{
			cfgFiles::writeDrawFrequencyToFile(log, path::getConfigDirFile(prefPath, file::DRAW_FREQ_FILE) );
		}
	}
}

void cfgFiles::writeDrawFrequencyToFile(LogFile& log, const std::string& drawFreqFilePath)
{
	if( std::ofstream drawFrequencyFile{drawFreqFilePath} )
	{
		drawFrequencyFile << 60;
	}
	else{
		log.wrFileOpeningError(drawFreqFilePath, "write draw frequency game value");
	}
}

void cfgFiles::createSoundConfigFile(LogFile& log, const PrefPathFinder& prefPath)
{
	if( prefPath.isAValidPathFound() )
	{
		if( createFs::FsNewCreated == createFs::mkNewFileIfMissing(path::getConfigDirFile(prefPath, file::SOUND_CFG_FILE) ) )
		{
			cfgFiles::writeSoundConfigFile(log, path::getConfigDirFile(prefPath, file::SOUND_CFG_FILE) );
		}
	}
}

void cfgFiles::writeSoundConfigFile(LogFile& log, const std::string& soundConfigFilePath)
{
	if( std::ofstream soundConfigFile{ soundConfigFilePath } )
	{
		soundConfigFile << "1 " << MIX_MAX_VOLUME / 2;
	}
	else{
		log.wrFileOpeningError(soundConfigFilePath, "write game sound configuration");
	}
}

void cfgFiles::createMusicConfigFile(LogFile& log, const PrefPathFinder& prefPath)
{
	if( prefPath.isAValidPathFound() )
	{
		if( createFs::FsNewCreated == createFs::mkNewFileIfMissing(path::getConfigDirFile(prefPath, file::MUSIC_CFG_FILE) ) )
		{
			cfgFiles::writeMusicConfigFile(log, path::getConfigDirFile(prefPath, file::MUSIC_CFG_FILE) );
		}
	}
}

void cfgFiles::writeMusicConfigFile(LogFile& log, const std::string& musicConfigFilePath)
{
	if( std::ofstream musicConfigFile{ musicConfigFilePath } )
	{
		musicConfigFile << "1 " << MIX_MAX_VOLUME / 2;
	}
	else{
		log.wrFileOpeningError(musicConfigFilePath, "game music configuration");
	}
}

void cfgFiles::createBestScoresFiles(LogFile& log, const PrefPathFinder& prefPath)
{
	for( unsigned skill{0} ; skill < onePlGame::SkillLevelMax ; ++skill )
	{
		if( createFs::FsNewError == createFs::mkNewFileIfMissing( path::getShopRaceBestScoresFilePath(prefPath, skill) ) )
		{
			log.wrFileOpeningError(path::getShopRaceBestScoresFilePath(prefPath, skill), "write 'shop race' one player scores");
		}
		if( createFs::FsNewError == createFs::mkNewFileIfMissing( path::getStdRaceBestScoresFilePath(prefPath, skill) ) )
		{
			log.wrFileOpeningError(path::getStdRaceBestScoresFilePath(prefPath, skill), "write 'standard race' one player score");
		}
	}
}