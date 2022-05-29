#ifndef ONE_PLAYER_BONUSES_CONSTS_H
#define ONE_PLAYER_BONUSES_CONSTS_H

#include "consts/constexprScreen.h"

namespace onePlGame{

enum{ BONUS_STICKY, BONUS_RACKET_SPEEDUP, BONUS_ENLARGE_RACKET, BONUS_ENLARGE_RIM, BONUS_POWERBALL, BONUS_ONE_UP, BONUS_MAX };

namespace bcost{

constexpr unsigned STICKY_RACK = 1;
constexpr unsigned RACK_SPEEDUP = 3;
constexpr unsigned RACK_ENLARGE = 5;
constexpr unsigned ENLARGE_RIM = 6;
constexpr unsigned POWER_BALL = 10;
constexpr unsigned ONE_UP = 12;

}

constexpr int ICONS_Y_POS = SQR_SIZE*10;//Only for the game not the 'Shop' context
constexpr int R_ICONS_X_POS = GAME_SCREEN_WIDTH - SQR_SIZE*3;//Only for the 'Shop', not the game context
constexpr int L_ICONS_X_POS = SQR_SIZE;//Only for the 'Shop', not the game context

}

#endif //ONE_PLAYER_BONUSES_CONSTS_H