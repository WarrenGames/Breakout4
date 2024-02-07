#ifndef ONE_P_IN_GAME_LVL_COMPONENTS_DEMOS_PLAYER_STARTING_DATA_H
#define ONE_P_IN_GAME_LVL_COMPONENTS_DEMOS_PLAYER_STARTING_DATA_H

#include <vector>

namespace demos
{

struct StartingData
{
	unsigned campaignType;
	unsigned levelIndex;
	unsigned skillLevel;
	unsigned playerLives;
	unsigned racketSize;
	unsigned score;
	unsigned bonusCoinsNumber;
	int rimsStartState;
	int squareSizeAtSaving;
	double racketSpeed;
	std::vector< unsigned > bonusesInBag;
	
	explicit StartingData();
	~StartingData() = default;
	StartingData( const StartingData& ) = default;
	StartingData& operator=( const StartingData& ) = default;
};

}

#endif //ONE_P_IN_GAME_LVL_COMPONENTS_DEMOS_PLAYER_STARTING_DATA_H