#ifndef DUELS_TYPES_H
#define DUELS_TYPES_H

#include "duels/zones/halloween/subObjects/halloweenConfig.h"
#include "duels/zones/metalStrings/subObjects/metalStringsConfig.h"
#include "consts/duelsConstexpr.h"

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
		unsigned currentZoneEnum;
		HalloweenConfig halloween;
		MetalStringsConfig metalStrings;
		
		explicit LevelOptions(AppLogFiles& logs, const PrefPathFinder& prefPath);
		~LevelOptions() = default;
		LevelOptions( const LevelOptions& ) = delete;
		LevelOptions& operator= ( const LevelOptions& ) = delete;
		LevelOptions( LevelOptions&& ) = default;
		LevelOptions& operator= ( LevelOptions&& ) = default;
		
		void avoidBadMaxValues();
		
		void setChampionshipEnd(unsigned finalScore, bool& quitZone) const;
		
		const fs::path& getSoundsListFilePath() const;
		const fs::path& getChannelsConfigFilePath() const;
		unsigned getExpectedSoundsNumber() const;
		int getExpectedGroupsTagNumber() const;
	};
}

#endif //DUELS_TYPES_H