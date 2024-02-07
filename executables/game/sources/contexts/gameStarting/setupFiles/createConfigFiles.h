#ifndef CREATE_CONFIG_FILES_AT_START_H
#define CREATE_CONFIG_FILES_AT_START_H

#include "fileSystem/fileSystem.h"

class LogFile;
class PrefPathFinder;

namespace cfgFiles{
	void createDrawFrequencyFile(LogFile& log, const PrefPathFinder& prefPath);
	
	void writeDrawFrequencyToFile(LogFile& log, const fs::path& drawFreqFilePath);
	
	void createSoundConfigFile(LogFile& log, const PrefPathFinder& prefPath);
	
	void writeSoundConfigFile(LogFile& log, const fs::path& configSoundFilePath);

	void createMusicConfigFile(LogFile& log, const PrefPathFinder& prefPath);
	
	void writeMusicConfigFile(LogFile& log, const fs::path& configSoundFilePath);
	
	void createBestScoresFiles(LogFile& log, const PrefPathFinder& prefPath);
	
	void createDisplaySdl2LogoStatusFile(LogFile& log, const PrefPathFinder& prefPath);
	
	void writeDisplaySdl2LogoStatusFile(LogFile& log, const fs::path& statusFile);
	
	void createDemosConfigFiles(LogFile& log, const PrefPathFinder& prefPath, const fs::path& fileName);
	
	void writeDemoConfigFile(LogFile& log, const fs::path& statusFile);
}

#endif //CREATE_CONFIG_FILES_AT_START_H