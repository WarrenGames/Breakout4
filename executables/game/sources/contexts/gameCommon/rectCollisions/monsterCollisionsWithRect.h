#ifndef MONSTER_COLLISION_WITH_RECT_H
#define MONSTER_COLLISION_WITH_RECT_H

struct SDL_Rect;
struct Offset;

namespace collision{

bool monsterIsOnLeftOfRacket(const SDL_Rect& racketRect, const SDL_Rect& monsterRect, const Offset& monsterPosition);

bool monsterIsOnRightOfRacket(const SDL_Rect& racketRect, const SDL_Rect& monsterRect, const Offset& monsterPosition);

bool isThereCollision(const SDL_Rect& racketRect, const SDL_Rect& monsterRect, const Offset& monsterPosition, int interval);

}

#endif //MONSTER_COLLISION_WITH_RECT_H