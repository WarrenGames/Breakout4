#ifndef CREATE_CONFIG_FILES_AT_START_H
#define CREATE_CONFIG_FILES_AT_START_H

#include <string>

class LogFile;
class PrefPathFinder;

namespace cfgFiles{
	void createDrawFrequencyFile(LogFile& log, const PrefPathFinder& prefPath);
	
	void writeDrawFrequencyToFile(LogFile& log, const std::string& drawFreqFilePath);
	
	void createSoundConfigFile(LogFile& log, const PrefPathFinder& prefPath);
	
	void writeSoundConfigFile(LogFile& log, const std::string& configSoundFilePath);

	void createMusicConfigFile(LogFile& log, const PrefPathFinder& prefPath);
	
	void writeMusicConfigFile(LogFile& log, const std::string& configSoundFilePath);
	
	void createBestScoresFiles(LogFile& log, const PrefPathFinder& prefPath);
}

#endif //CREATE_CONFIG_FILES_AT_START_H