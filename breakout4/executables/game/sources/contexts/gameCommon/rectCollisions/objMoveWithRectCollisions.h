#ifndef OBJ_MOVE_WITH_RECT_COLLISION_H
#define OBJ_MOVE_WITH_RECT_COLLISION_H

#include "consts/constexprScreen.h"

class ObjectMoving;
struct SpriteSize;
struct SDL_Rect;
class SoundHandler;

namespace rectCollision{

constexpr int BALL_INTERVAL = 12 * SQR_SIZE / 64;

void startCollisionTest(ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval, const SoundHandler& sounds, unsigned soundIndex);

bool doesAObjectCollideWithRect(const ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect);

void testTopCollision(ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval);
void testBottomCollision(ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval);
void testRightSideCollision(ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval);
void testLeftSideCollision(ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval);

void testTopLeftCornerCollision(ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval);
void testTopRightCornerCollision(ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval);
void testBottomLeftCornerCollision(ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval);
void testBottomRightCornerCollision(ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval);

bool isNearTopSide(const ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect);
bool isNearBottomSide(const ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect);
bool isNearLeftSide(const ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect);
bool isNearRightSide(const ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect);

}

#endif //OBJ_MOVE_WITH_RECT_COLLISION_H