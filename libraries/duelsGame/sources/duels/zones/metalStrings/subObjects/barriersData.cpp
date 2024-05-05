#include "duels/zones/metalStrings/subObjects/barriersData.h"
#include "duels/zones/metalStrings/subObjects/consts.h"
#include "consts/duelsConstexpr.h"

BarriersData::BarriersData():
	barrierMoveType{metalStrings::DirectionStop, metalStrings::DirectionStop},
	moveDelay(duels::PlayerMax),
	stopBeforeRegressDelay(duels::PlayerMax),
	forthBarriersPosition{metalStrings::TopBarY_Forth, metalStrings::BottomBarY_Forth},
	canBallCollideWithBarrier{true, true, true, true},
	canCoinCollideWithBarrier{true, true, true, true}
{
	
}