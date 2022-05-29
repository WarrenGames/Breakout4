#ifndef DUELS_POSITION_CHECK_H
#define DUELS_POSITION_CHECK_H

class ObjectMoving;
struct SpriteSize;
struct Offset;
struct SDL_Rect;

bool isElementInsideOfScreen(const ObjectMoving& objectMove, const SpriteSize& size);

bool isMoveObjectOverSpawnPoint(const ObjectMoving& move, const SpriteSize& size, const Offset& spawnPoint);

bool doesMoveObjectCollideWithRect(const ObjectMoving& move, const SpriteSize& size, const SDL_Rect& rect);

bool doesRectsCollide(const SDL_Rect& rectOne, const SDL_Rect& rectTwo);

#endif //DUELS_POSITION_CHECK_H