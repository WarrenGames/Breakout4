#ifndef GAME_COMMON_OBJ_MV_CENTER_AND_POS_WITH_COL_RECT_H
#define GAME_COMMON_OBJ_MV_CENTER_AND_POS_WITH_COL_RECT_H

namespace spriteMove{ class ObjectMoving; }
struct SpriteSize;
struct SDL_Rect;

//Collisions between an 'objectMove' with center object positioning ('moveA') and a top left object position ('moveB') with collision rect box ('collideRect') with an interval

namespace collision{

namespace objMvAndSingleColRect{

bool doCollide(const spriteMove::ObjectMoving& moveA, const SpriteSize& aSize, const spriteMove::ObjectMoving& moveB, const SDL_Rect& bCollideRect, int interval);

//Checking collision with 'doCollide' function should be performed first before calling function 'processBouncing'
void processBouncing(spriteMove::ObjectMoving& moveA, spriteMove::ObjectMoving& moveB, const SDL_Rect& bCollideRect);

void verticalBouncing(spriteMove::ObjectMoving& moveA, spriteMove::ObjectMoving& moveB);

void horizontalBouncing(spriteMove::ObjectMoving& moveA, spriteMove::ObjectMoving& moveB);

bool isOnX_a_before_b(spriteMove::ObjectMoving& moveA, spriteMove::ObjectMoving& moveB, const SDL_Rect& bCollideRect);

bool isOnX_a_on_b(spriteMove::ObjectMoving& moveA, spriteMove::ObjectMoving& moveB, const SDL_Rect& bCollideRect);

bool isOnX_a_after_b(spriteMove::ObjectMoving& moveA, spriteMove::ObjectMoving& moveB, const SDL_Rect& bCollideRect);

bool isOnY_a_before_b(spriteMove::ObjectMoving& moveA, spriteMove::ObjectMoving& moveB, const SDL_Rect& bCollideRect);

bool isOnY_a_on_b(spriteMove::ObjectMoving& moveA, spriteMove::ObjectMoving& moveB, const SDL_Rect& bCollideRect);

bool isOnY_a_after_b(spriteMove::ObjectMoving& moveA, spriteMove::ObjectMoving& moveB, const SDL_Rect& bCollideRect);

}

}

#endif //GAME_COMMON_OBJ_MV_CENTER_AND_POS_WITH_COL_RECT_H