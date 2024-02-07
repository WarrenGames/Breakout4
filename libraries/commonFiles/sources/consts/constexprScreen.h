#ifndef CONSTEXPR_SCREEN_H
#define CONSTEXPR_SCREEN_H

#include "consts/squareSize.h"

constexpr int GameSquaresWidth = 20;
constexpr int GameSquaresHeight = 15;

constexpr int GameScreenWidth = SQR_SIZE * GameSquaresWidth;
constexpr int GameScreenHeight = SQR_SIZE * GameSquaresHeight;

constexpr int MiniScreenWidth = 640;
constexpr int MiniScreenHeight = 400;

#ifndef NDEBUG
	constexpr char GameWindowTitle[] = "Breakout 4 - Debug mode";
#else
	constexpr char GameWindowTitle[] = "Breakout 4 - Release mode";
#endif 

constexpr unsigned SdlDelayTime = 16;

constexpr unsigned SdlMixerChannelsNumber = 16;

constexpr char BackgroundTexturePath[] = "textures/sprites/bricks/bgBrick.png";

#endif //CONSTEXPR_SCREEN_H