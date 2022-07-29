#ifndef HELL_CONSTS_H
#define HELL_CONSTS_H

#include "consts/constexprScreen.h"

namespace hell{
	enum{ 	ID_SKULL,
			ID_LAVA, 
			ID_MAX };
	
	enum{ 	FB_PATH_BELL_TRAJ_RIGHT,
			FB_PATH_BELL_TRAJ_LEFT,
			FB_PATH_BOTTOM_SCREEN,
			FB_PATH_CURVE_TO_RIGHT,
			FB_PATH_CURVE_TO_LEFT,
			FB_PATH_MAX };
	
	enum{
		SkullThrowFireBall,
		SkullRushToBall,
		SkullJobMax
	};
	
	constexpr int MOVE_DELAY = 10;
	
	constexpr double SkullStartSpeed = 2;
	constexpr double SkullRushSpeed = 6;
	
	constexpr unsigned SkullExplosionIndex = 0;
	
	constexpr int FireBallWidth = SQR_SIZE * 2 * 3 / 8;
}

#endif //HELL_CONSTS_H