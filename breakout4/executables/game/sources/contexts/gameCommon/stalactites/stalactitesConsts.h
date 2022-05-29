#ifndef GAME_COMMON_STALACTITES_CONSTS_H
#define GAME_COMMON_STALACTITES_CONSTS_H

#include "consts/constexprScreen.h"

namespace stalactites{

	constexpr int DIRECTIONS_NUMBER = 32;
	constexpr int DEFAULT_LENGTH = SQR_SIZE;
	constexpr int DEFAULT_DIRECTION = 24;
	
	constexpr char TEXTURES_FILE_PATH[] = "data/textures/iceStalactiteTextureList.txt";
	constexpr char RECTS_FILE_PATH[] = "data/textures/iceStalactiteRects.txt";
	constexpr int RECT_ID = 7;
	
	enum{ STATE_STATIC, STATE_RUMBLE, STATE_FALLING, STATE_OUT };
	
	constexpr int RUMBLE_MAX = 32;
	constexpr double FALL_SPEED = 4;
	constexpr unsigned RUMBLE_ANIM_DELAY = 40;
	constexpr unsigned FALL_SPEED_DELAY = 10;
}

#endif //GAME_COMMON_STALACTITES_CONSTS_H