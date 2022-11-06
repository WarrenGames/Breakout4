#ifndef DUELS_COLLISION_BOOLS_H
#define DUELS_COLLISION_BOOLS_H

struct CollisionBools
{
	bool canCheckCollisionWithCoins;
	bool canCheckCollisionWithBalls;
	bool canCheckCollisionWithRaquettes;
	bool canCheckCollisionWithGrid;
	bool canCheckCollisionWithScreenRim;
	
	CollisionBools();
	void resetAllCollisions();
};

#endif //DUELS_COLLISION_BOOLS_H