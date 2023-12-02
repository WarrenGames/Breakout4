#include "contexts/gameStarting/setupFiles/createConfigFiles.h"
#include "prefPath/prefPathFinder.h"
#include "logging/logFile.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "fileSystem/createNewElementFs.h"
#include "consts/constexprScreen.h"
#include "consts/onePlayerLevelConsts.h"
#include "demos/consts/demosConsts.h"
#include "SDL_mixer.h"

void cfgFiles::createDrawFrequencyFile(LogFile& log, const PrefPathFinder& prefPath)
{
	if( prefPath.isAValidPathFound() )
	{
		if( createFs::FsNewCreated == createFs::mkNewFileIfMissing(path::getConfigDirFile(prefPath, file::DrawFrequencyFile) ) )
		{
			cfgFiles::writeDrawFrequencyToFile(log, path::getConfigDirFile(prefPath, file::DrawFrequencyFile) );
		}
	}
}

void cfgFiles::writeDrawFrequencyToFile(LogFile& log, const fs::path& drawFreqFilePath)
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
		if( createFs::FsNewCreated == createFs::mkNewFileIfMissing(path::getConfigDirFile(prefPath, file::SoundConfigFile) ) )
		{
			cfgFiles::writeSoundConfigFile(log, path::getConfigDirFile(prefPath, file::SoundConfigFile) );
		}
	}
}

void cfgFiles::writeSoundConfigFile(LogFile& log, const fs::path& soundConfigFilePath)
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
		if( createFs::FsNewCreated == createFs::mkNewFileIfMissing(path::getConfigDirFile(prefPath, file::MusicConfigFile) ) )
		{
			cfgFiles::writeMusicConfigFile(log, path::getConfigDirFile(prefPath, file::MusicConfigFile) );
		}
	}
}

void cfgFiles::writeMusicConfigFile(LogFile& log, const fs::path& musicConfigFilePath)
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

void cfgFiles::createDisplaySdl2LogoStatusFile(LogFile& log, const PrefPathFinder& prefPath)
{
	if( prefPath.isAValidPathFound() )
	{
		if( createFs::FsNewCreated == createFs::mkNewFileIfMissing(path::getConfigDirFile(prefPath, file::DisplaySdl2LogoStatusFile ) ) )
		{
			cfgFiles::writeDisplaySdl2LogoStatusFile(log, path::getConfigDirFile(prefPath, file::DisplaySdl2LogoStatusFile) );
		}
	}
}

void cfgFiles::writeDisplaySdl2LogoStatusFile(LogFile& log, const fs::path& statusFile)
{
	if( std::ofstream displayLogoFile{ statusFile } )
	{
		displayLogoFile << "1";
	}
	else{
		log.wrFileOpeningError(statusFile, "write SDL2 logo displaying boolean (with value '1'");
	}
}

void cfgFiles::createDemosConfigFiles(LogFile& log, const PrefPathFinder& prefPath, const fs::path& fileName)
{
	if( prefPath.isAValidPathFound() )
	{
		if( createFs::FsNewCreated == createFs::mkNewFileIfMissing( path::getDemoConfigFile(prefPath, fileName.string() ) ) )
		{
			cfgFiles::writeDemoConfigFile(log, path::getDemoConfigFile(prefPath, fileName.string() ) );
		}
	}
}

void cfgFiles::writeDemoConfigFile(LogFile& log, const fs::path& statusFile)
{
	if( std::ofstream demoConfigFile{ statusFile } )
	{
		demoConfigFile << demos::DefaultReservedDataForRecording << '\n';
	}
	else{
		log.wrFileOpeningError(statusFile, "write demo config file data size with value '" + std::to_string( demos::DefaultReservedDataForRecording ) + "' .");
	}
}

