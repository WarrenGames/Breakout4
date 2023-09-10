#include "fileSystem/fileSystem.h"
#include <vector>
#include <sstream>

struct SoundSpecifications;
struct AppLogFiles;
struct SoundData;

namespace soundLoad{
	void readLines(AppLogFiles& logs, const fs::path& filePath, std::vector< SoundSpecifications >& sounds, bool& sndHandlerLoadWasPerfect);
	
	void loadSoundPath(AppLogFiles& logs, const fs::path& filePath, std::istringstream& lineStream, fs::path& soundPath, bool& wasLoadingPerfect, unsigned fileLineNumber);
	
	void loadGroupValue(AppLogFiles& logs, const fs::path& filePath, std::istringstream& lineStream, int& groupTag, bool& wasLoadingPerfect, unsigned fileLineNumber);
	
	void putDataIntoVector(AppLogFiles& logs, std::vector< SoundSpecifications >& sounds, const SoundData& soundData, bool& sndHandlerLoadWasPerfect);
}