#include "levelComponents/bonusCoins/coinSample.h"
#include "consts/onePlayerLevelConsts.h"

CoinSample::CoinSample(const Offset& startingPosition):
	pos{startingPosition},
	animationIndex{0}
{
	
}

void CoinSample::incrementAnimIndex()
{
	if( animationIndex + 1 < onePlGame::CoinFramesNumber )
		++animationIndex;
	else{
		animationIndex = 0;
	}
}