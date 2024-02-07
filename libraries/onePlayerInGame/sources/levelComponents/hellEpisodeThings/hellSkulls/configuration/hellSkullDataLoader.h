#ifndef ONE_PLAYER_HELL_SKULL_DATA_LOADER_H
#define ONE_PLAYER_HELL_SKULL_DATA_LOADER_H

#include "levelComponents/hellEpisodeThings/hellSkulls/configuration/skullFileData.h"
#include <vector>
#include <iosfwd>

struct Essentials;
struct PlayerData;

namespace onePlGame{

class HellSkullDataLoader
{
private:
	std::vector< SkullFileData > skulls;
	bool isLoadingPerfect;
	
public:
	explicit HellSkullDataLoader(Essentials& essentials, const PlayerData& playerData);
	~HellSkullDataLoader() = default;
	HellSkullDataLoader( const HellSkullDataLoader& ) = delete;
	HellSkullDataLoader& operator= ( const HellSkullDataLoader& ) = delete;
	HellSkullDataLoader( HellSkullDataLoader&& ) = default;
	HellSkullDataLoader& operator= ( HellSkullDataLoader&& ) = default;
	
	bool wasLoadingPerfect() const;
	
	void populateSkullDataCont(Essentials& essentials, const PlayerData& playerData);
	void readLinesOfConfigFile(Essentials& essentials, const PlayerData& playerData, std::ifstream& skullFile);
	
	std::size_t size() const;
	std::vector< SkullFileData >::const_iterator begin() const;
	std::vector< SkullFileData >::const_iterator end() const;
	const SkullFileData& operator[](std::size_t index) const;
};

}

#endif //ONE_PLAYER_HELL_SKULL_DATA_LOADER_H