#ifndef HELL_CONSTS_H
#define HELL_CONSTS_H

#include "consts/constexprScreen.h"

namespace hell{
	enum{ 	IdSkull,
			IdLava, 
			IdMax };
	
	enum{ 	FireBallBellPathWayRight,
			FireBallBellPathWayLeft,
			FireBallPathBottomScreen,
			FireBallPathCurveRight,
			FireBallPathCurveLeft,
			FireBallPathMax };
	
	enum{
		SkullThrowFireBall,
		SkullRushToBall,
		SkullJobMax
	};
	
	constexpr int MoveDelay = 10;
	
	constexpr double SkullStartSpeed = 2;
	constexpr double SkullRushSpeed = 6;
	
	constexpr unsigned SkullExplosionIndex = 0;
	
	constexpr int FireBallWidth = SQR_SIZE * 2 * 3 / 8;
}

#endif //HELL_CONSTS_H