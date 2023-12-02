#include "levelComponents/traceCross/traceCross.h"
#include "types/essentialsStruct.h"

TraceCross::TraceCross(Essentials& essentials):
	position{ GameScreenWidth / 2, GameScreenHeight - SQR_SIZE * 5},
	crossTexture{essentials.logs, essentials.rndWnd, "textures/sprites/cross/cross.png"},
	moveDelay{}
{
	
}

TraceCross::operator bool() const
{
	return crossTexture.texture;
}

void TraceCross::drawCross(Essentials& essentials, bool isMainBallActive)
{
	if( false == isMainBallActive )
		crossTexture.draw(essentials.rndWnd, position);
}