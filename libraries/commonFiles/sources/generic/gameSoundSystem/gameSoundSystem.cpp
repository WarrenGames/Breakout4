#include "generic/gameSoundSystem/gameSoundSystem.h"
#include "prefPath/prefPathFinder.h"
#include "logging/logsStruct.h"

GameSoundSystem::GameSoundSystem(AppLogFiles& logs, const PrefPathFinder& prefPath, const fs::path& soundsFileList, const fs::path& groupTagCfg, 
									unsigned expectedSoundsNumber, unsigned expectedGroupTagsNumber):
	soundSystemFilesPaths{ prefPath, soundsFileList, groupTagCfg },
	soundSystem{ logs, soundSystemFilesPaths.getPaths(), expectedSoundsNumber, expectedGroupTagsNumber}
{
	
}