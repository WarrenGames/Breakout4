#ifndef H_EDITBOXES_CONST
#define H_EDITBOXES_CONST

#include "SDL_pixels.h"

constexpr char BoxesArialFontPath[] = "fonts/arial.ttf";

constexpr int BoxesMarginSize = 1;
constexpr unsigned int BoxesCharSizeMax = 8;

constexpr SDL_Color BoxesEditBoxWhite = {255, 255, 255, 255};
constexpr SDL_Color BoxesEditBoxBlack = {0, 0, 0, 255};
constexpr SDL_Color BoxesActiveEditBox = {192, 192, 192, 255};
constexpr SDL_Color BoxesOffEditBox = {128, 128, 128, 255};
constexpr unsigned int BoxesCursorBlinkTime = 400; //Delay for cursor to blink

#endif //H_EDITBOXES_CONST