#ifndef FACTORY_DUEL_ZONE_CONSTS_H
#define FACTORY_DUEL_ZONE_CONSTS_H

#include "consts/constexprScreen.h"

namespace metalStrings{

enum{ OrientationHorizontal, OrientationVertical, OrientationMax };

enum{ DirectionForward, DirectionRegress, DirectionStop };

enum{ DirectionToRight, DirectionToLeft, DirectionHorizontalStop };
enum{ DirectionToSouth, DirectionToNorth, DirectionVerticalStop };
	
constexpr unsigned StringsFramesNumber = 64;

constexpr int TopBarY_Forth = 0;
constexpr int TopBarY_Back = SQR_SIZE * 4;
constexpr int BottomBarY_Forth = GameScreenHeight - SQR_SIZE * 4;
constexpr int BottomBarY_Back = SQR_SIZE * 7;

constexpr unsigned SwitchsTexturesNumber = 10;

}

#endif //FACTORY_DUEL_ZONE_CONSTS_H