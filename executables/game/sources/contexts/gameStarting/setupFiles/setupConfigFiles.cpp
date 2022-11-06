#include "contexts/gameStarting/setupFiles/setupConfigFiles.h"
#include "prefPath/prefPathFinder.h"
#include "logging/logsStruct.h"
#include "contexts/gameStarting/setupFiles/setupLanguageFile.h"
#include "contexts/gameStarting/setupFiles/createConfigFiles.h"
#include "fileSystem/copyFilesAndDirectories.h"
#include "fileSystem/createNewElementFs.h"
#include "consts/constPaths.h"

void setupFiles::copyConfigFilesDirectory(AppLogFiles& logs, const PrefPathFinder& prefPath)
{
	createFs::mkDirectoryIfMissing(prefPath.getPath(), "config");
	copyFs::directoriesRecursively(logs, "data/setup/config/1player", prefPath.getPath() + "config/1player");
	copyFs::directoriesRecursively(logs, "data/setup/config/duels", prefPath.getPath() + "config/duels");
	cfgFiles::createDrawFrequencyFile(logs.error, prefPath);
	cfgFiles::createSoundConfigFile(logs.error, prefPath);
	cfgFiles::createMusicConfigFile(logs.error, prefPath);
	createFs::mkDirectoryIfMissing(prefPath.getPath(), GameSavesDirectory);
	createFs::mkDirectoryIfMissing(prefPath.getPath(), ScoresDirectory);
	cfgFiles::createBestScoresFiles(logs.error, prefPath);
	setupFiles::createMainLanguageDirectory(logs, prefPath);
}