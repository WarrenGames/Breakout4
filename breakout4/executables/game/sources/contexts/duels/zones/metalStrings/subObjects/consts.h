#ifndef FACTORY_DUEL_ZONE_CONSTS_H
#define FACTORY_DUEL_ZONE_CONSTS_H

#include "consts/constexprScreen.h"

namespace metalStrings{

enum{ ORIENT_HORIZ, ORIENT_VERT, ORIENT_MAX };

enum{ DIR_FORWARD, DIR_REGRESS, DIR_STOP };

enum{ DIR_TO_RIGHT, DIR_TO_LEFT, DIR_HORIZ_STOP };
enum{ DIR_TO_SOUTH, DIR_TO_NORTH, DIR_VERT_STOP };
	
constexpr unsigned STRING_FRAMES_NUM = 64;

constexpr int TOP_BARR_Y_FORTH = 0;
constexpr int TOP_BARR_Y_BACK = SQR_SIZE * 4;
constexpr int BOTTOM_BARR_Y_FORTH = GAME_SCREEN_HEIGHT - SQR_SIZE * 4;
constexpr int BOTTOM_BARR_Y_BACK = SQR_SIZE * 7;

constexpr unsigned SWITCHS_TEX_NUM = 10;

}

#endif //FACTORY_DUEL_ZONE_CONSTS_H