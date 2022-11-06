#ifndef DUELS_BONUS_COINS_H
#define DUELS_BONUS_COINS_H

#include "spriteMove/objectMove.h"
#include "contexts/duels/inGameObjects/gameElements/collisionsInfos.h"

namespace duels{

struct ComboCoinData
{
	spriteMove::ObjectMoving move;
	unsigned animIndex;
	CollisionInfos collision;
	
	ComboCoinData();
	void bounceAgainstLeftOfScreen();
	void bounceAgainstRightOfScreen();
	void animateCoin();
	void moveCoin();
	void makeCoinEffective(const Offset& newPosition, const Offset& newDirVector);
};

}

#endif //DUELS_BONUS_COINS_H