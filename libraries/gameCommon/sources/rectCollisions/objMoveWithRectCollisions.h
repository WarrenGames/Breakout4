#ifndef OBJ_MOVE_WITH_RECT_COLLISION_H
#define OBJ_MOVE_WITH_RECT_COLLISION_H

#include "consts/constexprScreen.h"

namespace spriteMove{ class ObjectMoving; }
struct SpriteSize;
struct SDL_Rect;
class SoundHandler;

namespace rectCollision{

constexpr int BallInterval = 12 * SQR_SIZE / 64;

void startCollisionTest(spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval, const SoundHandler& sounds, unsigned soundIndex);

bool doesAObjectCollideWithRect(const spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect);

void testTopCollision(spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval);
void testBottomCollision(spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval);
void testRightSideCollision(spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval);
void testLeftSideCollision(spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval);

void testTopLeftCornerCollision(spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval);
void testTopRightCornerCollision(spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval);
void testBottomLeftCornerCollision(spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval);
void testBottomRightCornerCollision(spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval);

bool isNearTopSide(const spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect);
bool isNearBottomSide(const spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect);
bool isNearLeftSide(const spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect);
bool isNearRightSide(const spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect);

}

#endif //OBJ_MOVE_WITH_RECT_COLLISION_H