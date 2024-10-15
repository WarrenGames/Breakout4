#ifndef SDL2_COLORS_H
#define SDL2_COLORS_H

#include "SDL_pixels.h"

constexpr SDL_Color BlackColor = {0, 0, 0, 255};
constexpr SDL_Color WhiteColor = {255, 255, 255, 255};

constexpr SDL_Color RedColor = {255, 0, 0, 255};
constexpr SDL_Color GreenColor = {0, 255, 0, 255};
constexpr SDL_Color BlueColor = {0, 0, 255, 255};

constexpr SDL_Color YellowColor = {255, 255, 0, 255};
constexpr SDL_Color VioletColor = {255, 0, 255, 255};
constexpr SDL_Color CyanColor = {0, 255, 255, 255};

constexpr SDL_Color MediumGrayColor = {127, 127, 127, 255};

constexpr SDL_Color OrangeColor = {238, 126, 7, 255};

constexpr SDL_Color DarkGreenColor = {0, 191, 0, 255};

constexpr SDL_Color BrownColor = {131, 93, 24, 255};

constexpr SDL_Color DarkBlueColor = {0, 0, 96, 255};
constexpr SDL_Color DarkRedColor = {96, 0, 0, 255};

#endif //SDL2_COLORS_H