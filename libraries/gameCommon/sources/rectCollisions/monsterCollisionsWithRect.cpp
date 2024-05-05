#include "rectCollisions/monsterCollisionsWithRect.h"
#include "customTypes/positionTypes.h"
#include "SDL_rect.h"

bool collision::monsterIsOnLeftOfRacket(const SDL_Rect& racketRect, const SDL_Rect& monsterRect, const Offset& monsterPosition, int interval)
{
	return monsterPosition.y + monsterRect.y + monsterRect.h >= racketRect.y 
		&& monsterPosition.y + monsterRect.y <= racketRect.y + racketRect.h
		&& monsterPosition.x + monsterRect.x + monsterRect.w < racketRect.x + interval
		&& monsterPosition.x + monsterRect.x + monsterRect.w > racketRect.x - interval;
}

bool collision::monsterIsOnRightOfRacket(const SDL_Rect& racketRect, const SDL_Rect& monsterRect, const Offset& monsterPosition, int interval)
{
	return monsterPosition.y + monsterRect.y + monsterRect.h >= racketRect.y 
		&& monsterPosition.y + monsterRect.y <= racketRect.y + racketRect.h
		&& monsterPosition.x + monsterRect.x > racketRect.x + racketRect.w - interval
		&& monsterPosition.x + monsterRect.x < racketRect.x + racketRect.w + interval;
}

bool collision::isThereCollision(const SDL_Rect& racketRect, const SDL_Rect& monsterRect, const Offset& monsterPosition, int interval)
{
	return monsterPosition.x + monsterRect.x + monsterRect.w >= racketRect.x - interval //On racket's left collision test
		&& monsterPosition.x + monsterRect.x < racketRect.x + racketRect.w + interval //On racket's right collision test
		&& monsterPosition.y + monsterRect.y + monsterRect.h  >= racketRect.y - interval //On racket's top collision test
		&& monsterPosition.y + monsterRect.y < racketRect.y + racketRect.h + interval; //On racket's bottom collision test
}
