#include "generic/gameSoundSystem/soundsFileDataPaths.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "prefPath/prefPathFinder.h"
#include "soundSystem/soundsPathsConsts.h"
#include "consts/constPaths.h"

SoundSystemFilesPaths::SoundSystemFilesPaths(const PrefPathFinder& prefPath, const fs::path& soundsFileList, const fs::path& groupTagCfg):
	configFilesPaths(sounds::PATH_SND_MAX)
{
	setPaths(prefPath, soundsFileList, groupTagCfg);
}

const std::vector< fs::path >& SoundSystemFilesPaths::getPaths() const
{
	return configFilesPaths;
}

void SoundSystemFilesPaths::setPaths(const PrefPathFinder& prefPath, const fs::path& soundsFileList, const fs::path& groupTagCfg)
{
	configFilesPaths[sounds::PATH_SND_VOLUME] = path::getConfigDirFile(prefPath, file::SoundConfigFile);
	configFilesPaths[sounds::PATH_SND_WAVEFORM_LIST] = soundsFileList;
	configFilesPaths[sounds::PATH_SND_WAVEFORM_DIRECTORY] = SoundsChunksDir;
	configFilesPaths[sounds::PATH_SND_CHANNEL_CONFIG] = groupTagCfg;
}