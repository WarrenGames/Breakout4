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
	~CollisionBools() = default;
	CollisionBools( const CollisionBools& ) = default;
	CollisionBools& operator= ( const CollisionBools& ) = default;
	void resetAllCollisions();
};

#endif //DUELS_COLLISION_BOOLS_H