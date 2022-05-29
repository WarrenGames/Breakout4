#ifndef OBJECT_MOVE_WITH_RECT_COLLIDE_H
#define OBJECT_MOVE_WITH_RECT_COLLIDE_H

class ObjectMoving;
struct SpriteSize;
struct SDL_Rect;

namespace collision{

void makeObjectMoveBounceWithRect(ObjectMoving& objectMove, const SpriteSize& objectSize, const SDL_Rect& rect);

void checkYPosition(ObjectMoving& objectMove, const SpriteSize& objectSize, const SDL_Rect& rect);

}

#endif //OBJECT_MOVE_WITH_RECT_COLLIDE_H