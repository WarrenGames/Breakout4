#include "contexts/duels/zones/metalStrings/subObjects/barriersData.h"
#include "contexts/duels/zones/metalStrings/subObjects/consts.h"

BarriersData::BarriersData():
	barrierMoveType{metalStrings::DIR_STOP, metalStrings::DIR_STOP},
	forthBarriersPosition{metalStrings::TOP_BARR_Y_FORTH, metalStrings::BOTTOM_BARR_Y_FORTH},
	canBallCollideWithBarrier{true, true, true, true},
	canCoinCollideWithBarrier{true, true, true, true}
{
	
}