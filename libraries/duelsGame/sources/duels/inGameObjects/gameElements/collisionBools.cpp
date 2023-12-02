#include "duels/inGameObjects/gameElements/collisionBools.h"

CollisionBools::CollisionBools():
	canCheckCollisionWithCoins{true},
	canCheckCollisionWithBalls{true},
	canCheckCollisionWithRaquettes{true},
	canCheckCollisionWithGrid{true},
	canCheckCollisionWithScreenRim{true}
{
	
}

void CollisionBools::resetAllCollisions()
{
	canCheckCollisionWithCoins = true;
	canCheckCollisionWithBalls = true;
	canCheckCollisionWithRaquettes = true;
	canCheckCollisionWithGrid = true;
	canCheckCollisionWithScreenRim = true;
}