#ifndef CONSTEXPR_SCREEN_H
#define CONSTEXPR_SCREEN_H

#include "consts/squareSize.h"

constexpr int GAME_SQUARES_WIDTH = 20;
constexpr int GAME_SQUARES_HEIGHT = 15;

constexpr int GAME_SCREEN_WIDTH = SQR_SIZE * GAME_SQUARES_WIDTH;
constexpr int GAME_SCREEN_HEIGHT = SQR_SIZE * GAME_SQUARES_HEIGHT;

constexpr int EDITOR_SQUARES_WIDTH = 20;
constexpr int EDITOR_SQUARES_HEIGHT = 15;

constexpr int EDITOR_SCREEN_WIDTH = SQR_SIZE * EDITOR_SQUARES_WIDTH;
constexpr int EDITOR_SCREEN_HEIGHT = SQR_SIZE * EDITOR_SQUARES_HEIGHT;

constexpr int SCREENW_MINI = 640;
constexpr int SCREENH_MINI = 400;

#ifndef NDEBUG
	constexpr char GAME_WINDOW_TITLE[] = "Breakout 4 - Debug mode";
#else
	constexpr char GAME_WINDOW_TITLE[] = "Breakout 4 - Release mode";
#endif 

#ifndef NDEBUG
	constexpr char EDITOR_WINDOW_TITLE[] = "Breakout 4 editor - Debug mode";
#else
	constexpr char EDITOR_WINDOW_TITLE[] = "Breakout 4 editor - Release mode";
#endif 

#define SQR_POW(value) value * value

constexpr unsigned SDL_DELAY_TIME = 16;

constexpr unsigned SDL_MIXER_CHANNELS_NUM = 16;

constexpr char BG_TEXTURE_PATH[] = "textures/sprites/bricks/bgBrick.png";

#endif //CONSTEXPR_SCREEN_H