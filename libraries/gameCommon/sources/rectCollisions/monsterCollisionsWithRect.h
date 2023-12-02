#ifndef MONSTER_COLLISION_WITH_RECT_H
#define MONSTER_COLLISION_WITH_RECT_H

struct SDL_Rect;
struct Offset;

namespace collision{

bool monsterIsOnLeftOfRacket(const SDL_Rect& racketRect, const SDL_Rect& monsterRect, const Offset& monsterPosition, int interval);

bool monsterIsOnRightOfRacket(const SDL_Rect& racketRect, const SDL_Rect& monsterRect, const Offset& monsterPosition, int interval);

//Here: giving a positive value to 'interval' enlarge the collision rect, making suitable to reset collision possibility with a boolean if the returning value
//		of the function is equal to false.
//Here:	giving a negative value to 'interval' ensure that the collision is at least real
bool isThereCollision(const SDL_Rect& racketRect, const SDL_Rect& monsterRect, const Offset& monsterPosition, int interval);

}

#endif //MONSTER_COLLISION_WITH_RECT_H