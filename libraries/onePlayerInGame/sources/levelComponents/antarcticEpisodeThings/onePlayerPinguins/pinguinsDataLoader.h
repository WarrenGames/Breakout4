#ifndef ONE_PLAYER_GAME_PINGUINS_DATA_LOADER_H
#define ONE_PLAYER_GAME_PINGUINS_DATA_LOADER_H

#include "levelComponents/monsters/pinguinBehaviorData.h"
#include <vector>
#include <string>
#include <sstream>

struct Essentials;
struct PlayerData;
struct AppLogFiles;

namespace onePlGame{

class PinguinsDataLoader
{
private:
	std::vector< PinguinBehaviorData > loadedData;
	unsigned revokingHits;
	bool isLoadingPerfect;

public:
	explicit PinguinsDataLoader(Essentials& essentials, const PlayerData& playerData);
	~PinguinsDataLoader() = default;
	PinguinsDataLoader( const PinguinsDataLoader& ) = delete;
	PinguinsDataLoader& operator= ( const PinguinsDataLoader& ) = delete;
	PinguinsDataLoader( PinguinsDataLoader&& ) = default;
	PinguinsDataLoader& operator= ( PinguinsDataLoader&& ) = default;
	
	bool wasLoadingPerfect() const;
	unsigned getRevokingHits() const;
	std::vector< PinguinBehaviorData >::iterator begin();
	std::vector< PinguinBehaviorData >::iterator end();
	
private:
	void loadDataFile(AppLogFiles& logs, const std::string& levelDataFilePath);
	void readSingleLine(AppLogFiles& logs, const std::string& levelDataFilePath, std::istringstream& lineStream, unsigned lineIndex);
	void loadPinguinData(AppLogFiles& logs, const std::string& levelDataFilePath, std::istringstream& lineStream);
	void loadNeededHitsData(AppLogFiles& logs, unsigned skillLevel);
};

}

#endif //ONE_PLAYER_GAME_PINGUINS_DATA_LOADER_H