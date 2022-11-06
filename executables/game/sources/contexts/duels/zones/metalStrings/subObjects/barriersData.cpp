#include "contexts/duels/zones/metalStrings/subObjects/barriersData.h"
#include "contexts/duels/zones/metalStrings/subObjects/consts.h"
#include "contexts/duels/duelsConstexpr.h"

BarriersData::BarriersData():
	barrierMoveType{metalStrings::DirectionStop, metalStrings::DirectionStop},
	moveDelay(duels::PlayerMax),
	stopBeforeRegressDelay(duels::PlayerMax),
	forthBarriersPosition{metalStrings::TopBarY_Forth, metalStrings::BottomBarY_Forth},
	canBallCollideWithBarrier{true, true, true, true},
	canCoinCollideWithBarrier{true, true, true, true}
{
	
}