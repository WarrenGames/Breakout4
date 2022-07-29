#ifndef DUELS_TYPES_H
#define DUELS_TYPES_H

#include "contexts/duels/zones/halloween/subObjects/halloweenConfig.h"
#include "contexts/duels/zones/metalStrings/subObjects/metalStringsConfig.h"
#include "contexts/duels/duelsConstexpr.h"

struct AppLogFiles;
class PrefPathFinder;

namespace duels{
	
	struct LevelOptions
	{
		std::vector< unsigned > bonuses;
		std::vector< int > playersScores;
		unsigned pointsToPlayInZone;
		unsigned secondsBeforeNewCoin;
		unsigned coinsMax;
		unsigned secondsBeforeNewBall;
		unsigned ballsMax;
		
		HalloweenConfig halloween;
		MetalStringsConfig metalStrings;
		
		explicit LevelOptions(AppLogFiles& logs, const PrefPathFinder& prefPath);
		void avoidBadMaxValues();
		
		void setChampionshipEnd(unsigned finalScore, bool& quitZone) const;
	};
}

#endif //DUELS_TYPES_H