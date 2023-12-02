#include "duels/inGameObjects/gameElements/spawnsData.h"

duels::SpawnsData::SpawnsData(unsigned seconds, unsigned max, const std::vector< Offset >& coordinates):
	secondsBeforeNewElement{seconds},
	maxElementNumber{max},
	canSpawnElement{true},
	newElementDelay{},
	spawnsCoordinates{coordinates}
{
	
}