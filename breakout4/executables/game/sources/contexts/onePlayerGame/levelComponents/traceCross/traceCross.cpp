#include "contexts/onePlayerGame/levelComponents/traceCross/traceCross.h"
#include "types/essentialsStruct.h"

TraceCross::TraceCross(Essentials& essentials):
	position{ GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT - SQR_SIZE * 5},
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