#include "contexts/gameCommon/rectCollisions/monsterCollisionsWithRect.h"
#include "customTypes/positionTypes.h"
#include "consts/constexprScreen.h"
#include "SDL_rect.h"

bool collision::monsterIsOnLeftOfRacket(const SDL_Rect& racketRect, const SDL_Rect& monsterRect, const Offset& monsterPosition)
{
	if( monsterPosition.y + monsterRect.h / 2 >= racketRect.y 
		&& monsterPosition.y - monsterRect.h / 2 <= racketRect.y + racketRect.h )
	{
		if( monsterPosition.x + monsterRect.w / 2 >= racketRect.x
			&& monsterPosition.x + monsterRect.w / 2 < racketRect.x + SQR_SIZE / 2 )
		{
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

bool collision::monsterIsOnRightOfRacket(const SDL_Rect& racketRect, const SDL_Rect& monsterRect, const Offset& monsterPosition)
{
	if( monsterPosition.y + monsterRect.h / 2 >= racketRect.y 
		&& monsterPosition.y - monsterRect.h / 2 <= racketRect.y + racketRect.h )
	{
		if( monsterPosition.x - monsterRect.w / 2 < racketRect.x + racketRect.w 
			&& monsterPosition.x - monsterRect.w / 2 >= racketRect.x + racketRect.w - SQR_SIZE / 2 )
		{
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

bool collision::isThereCollision(const SDL_Rect& racketRect, const SDL_Rect& monsterRect, const Offset& monsterPosition, int interval)
{
	return monsterPosition.x + monsterRect.w / 2 >= racketRect.x - interval
			&& monsterPosition.x - monsterRect.w / 2 < racketRect.x + racketRect.w + interval 
			&& monsterPosition.y + monsterRect.h / 2 >= racketRect.y - interval
			&& monsterPosition.y - monsterRect.h / 2 < racketRect.y + racketRect.h + interval; 
}
