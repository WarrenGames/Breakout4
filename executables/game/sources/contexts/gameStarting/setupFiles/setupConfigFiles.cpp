#include "contexts/gameStarting/setupFiles/setupConfigFiles.h"
#include "prefPath/prefPathFinder.h"
#include "logging/logsStruct.h"
#include "contexts/gameStarting/setupFiles/setupLanguageFile.h"
#include "contexts/gameStarting/setupFiles/createConfigFiles.h"
#include "fileSystem/copyFilesAndDirectories.h"
#include "fileSystem/createNewElementFs.h"
#include "consts/constPaths.h"
#include "generic/fileSystem/fileProcessing/filesNames.h"

void setupFiles::copyConfigFilesDirectory(AppLogFiles& logs, const PrefPathFinder& prefPath)
{
	createFs::mkDirectoryIfMissing(prefPath.getFsPath(), "config");
	createFs::mkDirectoryIfMissing(prefPath.getFsPath(), DemosFilesDirectory);
	copyFs::directoriesRecursively(logs, "data/setup/config/1player", prefPath.getPath() + "config/1player");
	copyFs::directoriesRecursively(logs, "data/setup/config/duels", prefPath.getPath() + "config/duels");
	cfgFiles::createDrawFrequencyFile(logs.error, prefPath);
	cfgFiles::createSoundConfigFile(logs.error, prefPath);
	cfgFiles::createMusicConfigFile(logs.error, prefPath);
	createFs::mkDirectoryIfMissing(prefPath.getFsPath(), GameSavesDirectory);
	createFs::mkDirectoryIfMissing(prefPath.getFsPath(), ScoresDirectory);
	cfgFiles::createBestScoresFiles(logs.error, prefPath);
	cfgFiles::createDisplaySdl2LogoStatusFile(logs.error, prefPath);
	setupFiles::createMainLanguageDirectory(logs, prefPath);
	cfgFiles::createDemosConfigFiles(logs.error, prefPath, file::DemoInputDataFile);
	cfgFiles::createDemosConfigFiles(logs.error, prefPath, file::DemoQuitEventFile);
	cfgFiles::createDemosConfigFiles(logs.error, prefPath, file::DemoTraceCrossPositionFile);
	cfgFiles::createDemosConfigFiles(logs.error, prefPath, file::DemoBallPositionFile);
	cfgFiles::createDemosConfigFiles(logs.error, prefPath, file::DemoRacketPositionFile);
	cfgFiles::createDemosConfigFiles(logs.error, prefPath, file::DemoBrickDestructionFile);
	cfgFiles::createDemosConfigFiles(logs.error, prefPath, file::DemoSoundsEventsFile);
	cfgFiles::createDemosConfigFiles(logs.error, prefPath, file::DemoPinguinsFile);
}