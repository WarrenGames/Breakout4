#include <string>
#include <vector>
#include <sstream>

struct SoundSpecifications;
class LogFile;
struct SoundData;

namespace soundLoad{
	void readLines(LogFile& log, const std::string& filePath, std::vector< SoundSpecifications >& sounds, bool& sndHandlerLoadWasPerfect);
	
	void loadSoundPath(LogFile& log, const std::string& filePath, std::istringstream& lineStream, std::string& soundPath, bool& wasLoadingPerfect, unsigned fileLineNumber);
	
	void loadGroupValue(LogFile& log, const std::string& filePath, std::istringstream& lineStream, int& groupTag, bool& wasLoadingPerfect, unsigned fileLineNumber);
	
	void putDataIntoVector(LogFile& log, std::vector< SoundSpecifications >& sounds, const SoundData& soundData, bool& sndHandlerLoadWasPerfect);
}