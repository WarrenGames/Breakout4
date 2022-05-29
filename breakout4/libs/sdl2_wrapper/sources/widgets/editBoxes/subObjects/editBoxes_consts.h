#ifndef H_EDITBOXES_CONST
#define H_EDITBOXES_CONST

#include "SDL.h"

constexpr char BOXES_ARIALFONTPATH[] = "fonts/arial.ttf";
constexpr unsigned int ARIAL_PTSIZE = 16;
constexpr int MARGIN_SIZE = 1;
constexpr unsigned int CHARSIZEMAX = 8;

constexpr SDL_Color ED_BOX_WHITE = {255, 255, 255, 255};
constexpr SDL_Color ED_BOX_BLACK = {0, 0, 0, 255};
constexpr SDL_Color ACTIVE_ED_BOX = {192, 192, 192, 255};
constexpr SDL_Color OFF_BOX = {128, 128, 128, 255};
constexpr unsigned int CURSOR_BLINK_TIME = 400; //Delay for cursor to blink

#endif //H_EDITBOXES_CONST