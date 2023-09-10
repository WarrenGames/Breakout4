#ifndef GAME_COMMON_STALACTITES_CONSTS_H
#define GAME_COMMON_STALACTITES_CONSTS_H

#include "consts/constexprScreen.h"

namespace stalactites{

	constexpr int DirectionsNumber = 32;
	constexpr int DefaultLength = SQR_SIZE;
	constexpr int DefaultDirection = 24;
	
	constexpr char TexturesFilePath[] = "data/textures/iceStalactiteTextureList.txt";
	constexpr char RectsFilePath[] = "data/textures/iceStalactiteRects.txt";
	constexpr int RectId = 7;
	
	enum{ StateStatic, StateRumble, StateFalling, StateOut };
	
	constexpr int RumbleMax = 32;
	constexpr double FallSpeed = 4;
	constexpr unsigned RumbleAnimDelay = 40;
	constexpr unsigned FallSpeedDelay = 10;
}

#endif //GAME_COMMON_STALACTITES_CONSTS_H