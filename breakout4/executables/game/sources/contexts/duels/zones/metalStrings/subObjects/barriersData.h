#ifndef METAL_STRINGS_BARRIERS_DATA_H
#define METAL_STRINGS_BARRIERS_DATA_H

#include "time/accurateTime.h"
#include "contexts/duels/duelsConstexpr.h"
#include <array>

struct BarriersData
{
	std::array< unsigned, duels::PLAYER_MAX >  barrierMoveType;
	std::array< AccurateTimeDelay, duels::PLAYER_MAX > moveDelay;
	std::array< AccurateTimeDelay, duels::PLAYER_MAX > stopBeforeRegressDelay;
	std::array< int, duels::PLAYER_MAX > forthBarriersPosition;
	
	std::array< bool, duels::BALL_MAX > canBallCollideWithBarrier;
	std::array< bool, duels::COIN_MAX > canCoinCollideWithBarrier;
	
	explicit BarriersData();
};

#endif //METAL_STRINGS_BARRIERS_DATA_H