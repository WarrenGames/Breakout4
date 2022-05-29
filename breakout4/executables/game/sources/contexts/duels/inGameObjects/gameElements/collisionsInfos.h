#ifndef DUELS_COMBO_OBJECTS_H
#define DUELS_COMBO_OBJECTS_H

#include "contexts/duels/duelsConstexpr.h"
#include <array>

namespace duels{

struct CollisionInfos
{
	bool isEffective;
	bool canCheckWZoneGrid;
	std::array<bool, duels::COIN_MAX> checkWCoinCollision;
	std::array<bool, duels::BALL_MAX> checkWBallCollision;
	std::array<bool, duels::PLAYER_MAX> checkWRacketsCollisions;
	
	CollisionInfos();
	void resetAllCollisions();
	void resetAllCoinsCollisions();
	void resetAllBallCollisions();
	void resetAllRacketsCollisions();
};
	

}
#endif //DUELS_COMBO_OBJECTS_H