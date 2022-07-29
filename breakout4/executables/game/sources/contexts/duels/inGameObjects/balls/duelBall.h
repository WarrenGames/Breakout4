#ifndef DUELS_BALL_H
#define DUELS_BALL_H

#include "spriteMove/objectMove.h"
#include "contexts/duels/inGameObjects/gameElements/collisionsInfos.h"
#include "matrices/matrix2D.h"

namespace duels{

struct ComboBallData
{
	spriteMove::ObjectMoving move;
	CollisionInfos collision;
	
	ComboBallData();
	
	void bounceAgainstLeftOfScreen(int ballTextureWidth);
	void bounceAgainstRightOfScreen(int ballTextureWidth);
	void makeBallEffective(const Offset& newPosition, const Offset& newDirVector);
};

}

#endif //DUELS_BALL_H