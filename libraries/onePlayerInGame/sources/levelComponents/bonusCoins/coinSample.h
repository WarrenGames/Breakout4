#ifndef ONE_PLAYER_COIN_SAMPLE_OBJ_H
#define ONE_PLAYER_COIN_SAMPLE_OBJ_H

#include "customTypes/positionTypes.h"
#include <cstddef>

struct CoinSample
{
	Offset pos;
	unsigned animationIndex;
	
	explicit CoinSample(const Offset& startingPosition);
	~CoinSample() = default;
	CoinSample( const CoinSample& ) = delete;
	CoinSample& operator= ( const CoinSample& ) = delete;
	CoinSample( CoinSample&& ) = default;
	CoinSample& operator= ( CoinSample&& ) = default;
	
	void incrementAnimIndex();
};

#endif //ONE_PLAYER_COIN_SAMPLE_OBJ_H