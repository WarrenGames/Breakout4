#include "contexts/onePlayerGame/levelComponents/bonusCoins/coinSample.h"
#include "consts/onePlayerLevelConsts.h"

CoinSample::CoinSample(const Offset& startingPosition):
	pos{startingPosition},
	animationIndex{0}
{
	
}

void CoinSample::incrementAnimIndex()
{
	if( animationIndex + 1 < onePlGame::COIN_FRAMES_NUMBER )
		++animationIndex;
	else{
		animationIndex = 0;
	}
}