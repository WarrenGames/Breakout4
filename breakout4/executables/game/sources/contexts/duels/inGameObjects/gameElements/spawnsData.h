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
	const std::vector< Offset > spawnsCoordinates;

	explicit SpawnsData(unsigned seconds, unsigned max, const std::vector< Offset >& coordinates);
};

}

#endif //DUELS_SPAWNS_DATA_H