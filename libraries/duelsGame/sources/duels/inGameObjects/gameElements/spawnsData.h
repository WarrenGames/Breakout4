#ifndef DUELS_SPAWNS_DATA_H
#define DUELS_SPAWNS_DATA_H

#include "time/accurateTime.h"
#include "customTypes/positionTypes.h"
#include <vector>

namespace duels{

struct SpawnsData
{
	unsigned secondsBeforeNewElement;
	unsigned maxElementNumber;
	bool canSpawnElement;
	AccurateTimeDelay newElementDelay;
	std::vector< Offset > spawnsCoordinates;

	explicit SpawnsData(unsigned seconds, unsigned max, const std::vector< Offset >& coordinates);
	~SpawnsData() = default;
	SpawnsData( const SpawnsData& ) = delete;
	SpawnsData& operator= ( const SpawnsData& ) = delete;
	SpawnsData( SpawnsData&& ) = default;
	SpawnsData& operator= ( SpawnsData&& ) = default;
};

}

#endif //DUELS_SPAWNS_DATA_H