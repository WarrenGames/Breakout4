#ifndef ONE_PLAYER_GAME_ICE_STALACTITES_DATA_LOADING_H
#define ONE_PLAYER_GAME_ICE_STALACTITES_DATA_LOADING_H

#include "stalactites/onePlayerStalactiteData.h"
#include <vector>

struct Essentials;
struct PlayerData;

namespace onePlGame{

class StalactitesLoading
{
private:
	std::vector< OnePlayerStalactiteData > data;
	bool isLoadingPerfect;

public:
	explicit StalactitesLoading(Essentials& essentials, const PlayerData& playerData);
	~StalactitesLoading() = default;
	StalactitesLoading( const StalactitesLoading& ) = delete;
	StalactitesLoading& operator= ( const StalactitesLoading& ) = delete;
	StalactitesLoading( StalactitesLoading&& ) = default;
	StalactitesLoading& operator= ( StalactitesLoading&& ) = default;
	
	bool wasLoadingPerfect() const;
	std::vector< OnePlayerStalactiteData >& getData();

private:
	void loadStalactitesConfig(Essentials& essentials, const PlayerData& playerData);
	void loadSingleStalactite(Essentials& essentials, const PlayerData& playerData, std::istringstream& lineStream, unsigned lineNum);
	void logEverythingWentFine(Essentials& essentials, const PlayerData& playerData) const;
};

}

#endif //ONE_PLAYER_GAME_ICE_STALACTITES_DATA_LOADING_H