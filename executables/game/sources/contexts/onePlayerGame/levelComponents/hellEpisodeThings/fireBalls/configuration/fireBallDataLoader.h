#ifndef ONE_PLAYER_FIRE_BALLS_DATA_LOADER_H
#define ONE_PLAYER_FIRE_BALLS_DATA_LOADER_H

#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/fireBalls/configuration/fireBallFileData.h"
#include <vector>
#include <iosfwd>

struct Essentials;
struct PlayerData;

namespace onePlGame{

class FireBallDataLoader
{
private:
	std::vector< FireBallFileData > fireBalls;
	bool isLoadingPerfect;
	
public:
	explicit FireBallDataLoader(Essentials& essentials, const PlayerData& playerData);
	~FireBallDataLoader() = default;
	FireBallDataLoader( const FireBallDataLoader& ) = delete;
	FireBallDataLoader& operator= ( const FireBallDataLoader& ) = delete;
	FireBallDataLoader( FireBallDataLoader&& ) = default;
	FireBallDataLoader& operator= ( FireBallDataLoader&& ) = default;
	
	bool wasLoadingPerfect() const;
	
	void populateFireBallsCont(Essentials& essentials, const PlayerData& playerData);
	void readLinesOfConfigFile(Essentials& essentials, const PlayerData& playerData, std::ifstream& fireBallFile);
	
	std::vector< FireBallFileData >::const_iterator begin() const;
	std::vector< FireBallFileData >::const_iterator end() const;
};

}

#endif //ONE_PLAYER_FIRE_BALLS_DATA_LOADER_H