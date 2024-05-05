#ifndef METAL_STRINGS_BARRIERS_DATA_H
#define METAL_STRINGS_BARRIERS_DATA_H

#include "time/accurateTime.h"
#include <vector>

struct BarriersData
{
	std::vector< unsigned >  barrierMoveType;
	std::vector< AccurateTimeDelay > moveDelay;
	std::vector< AccurateTimeDelay > stopBeforeRegressDelay;
	std::vector< int > forthBarriersPosition;
	
	std::vector< bool > canBallCollideWithBarrier;
	std::vector< bool > canCoinCollideWithBarrier;
	
	explicit BarriersData();
	~BarriersData() = default;
	BarriersData( const BarriersData& ) = delete;
	BarriersData& operator= ( const BarriersData& ) = delete;
	BarriersData( BarriersData&& ) = default;
	BarriersData& operator= ( BarriersData&& ) = default;
};

#endif //METAL_STRINGS_BARRIERS_DATA_H