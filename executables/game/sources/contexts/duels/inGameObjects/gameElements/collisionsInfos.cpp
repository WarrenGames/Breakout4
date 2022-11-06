#include "contexts/duels/inGameObjects/gameElements/collisionsInfos.h"
#include "contexts/duels/duelsConstexpr.h"
#include <algorithm>

duels::CollisionInfos::CollisionInfos():
	isEffective{false},
	canCheckWZoneGrid{true},
	checkWCoinCollision(duels::CoinMaxNumber, true),
	checkWBallCollision(duels::BallMaxNumber, true),
	checkWRacketsCollisions(duels::PlayerMax, true)
{}

void duels::CollisionInfos::resetAllCollisions()
{
	isEffective = true;
	canCheckWZoneGrid = true;
	resetAllCoinsCollisions();
	resetAllBallCollisions();
	resetAllRacketsCollisions();
}

void duels::CollisionInfos::resetAllCoinsCollisions()
{
	std::fill(checkWCoinCollision.begin(), checkWCoinCollision.end(), true);
}

void duels::CollisionInfos::resetAllBallCollisions()
{
	std::fill(checkWBallCollision.begin(), checkWBallCollision.end(), true);
}

void duels::CollisionInfos::resetAllRacketsCollisions()
{
	std::fill(checkWRacketsCollisions.begin(), checkWRacketsCollisions.end(), true);
}
