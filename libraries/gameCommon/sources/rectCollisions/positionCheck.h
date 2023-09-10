#ifndef DUELS_POSITION_CHECK_H
#define DUELS_POSITION_CHECK_H

namespace spriteMove{ class ObjectMoving; }
struct SpriteSize;
struct Offset;
struct SDL_Rect;

bool isElementInsideOfScreen(const spriteMove::ObjectMoving& objectMove, const SpriteSize& size);

bool isMoveObjectOverSpawnPoint(const spriteMove::ObjectMoving& move, const SpriteSize& size, const Offset& spawnPoint);

bool doesMoveObjectCollideWithRect(const spriteMove::ObjectMoving& move, const SpriteSize& size, const SDL_Rect& rect);

bool doesRectsCollide(const SDL_Rect& rectOne, const SDL_Rect& rectTwo);

#endif //DUELS_POSITION_CHECK_H