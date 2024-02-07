#ifndef DUELS_COMBO_OBJECTS_H
#define DUELS_COMBO_OBJECTS_H

#include <vector>

namespace duels{

struct CollisionInfos
{
	bool isEffective;
	bool canCheckWZoneGrid;
	std::vector< bool > checkWCoinCollision;
	std::vector< bool > checkWBallCollision;
	std::vector< bool > checkWRacketsCollisions;
	
	CollisionInfos();
	~CollisionInfos() = default;
	CollisionInfos( const CollisionInfos& ) = default;
	CollisionInfos& operator= ( const CollisionInfos& ) = default;
	void resetAllCollisions();
	void resetAllCoinsCollisions();
	void resetAllBallCollisions();
	void resetAllRacketsCollisions();
};
	

}
#endif //DUELS_COMBO_OBJECTS_H