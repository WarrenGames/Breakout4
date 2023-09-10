#ifndef ONE_PLAYER_BONUSES_CONSTS_H
#define ONE_PLAYER_BONUSES_CONSTS_H

#include "consts/constexprScreen.h"

namespace onePlGame{

enum{ BonusStickyRacket, BonusRacketSpeedUp, BonusEnlargeRacket, BonusEnlargeRim, BonusPowerBall, BonusOneMoreBallLive, BonusMax };

namespace bcost{

constexpr unsigned StickyRacket = 1;
constexpr unsigned RacketSpeedUp = 3;
constexpr unsigned EnlargeRacket = 5;
constexpr unsigned EnlargeRims = 6;
constexpr unsigned PowerBall = 10;
constexpr unsigned OneUp = 12;

}

constexpr double RacketSpeedBonusAdd = 0.5 * SQR_SIZE / 64.0;

}

#endif //ONE_PLAYER_BONUSES_CONSTS_H