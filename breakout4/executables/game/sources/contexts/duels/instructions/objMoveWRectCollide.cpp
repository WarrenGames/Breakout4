#include "contexts/duels/instructions/objMoveWRectCollide.h"
#include "spriteMove/objectMove.h"
#include "types/spriteSize.h"
#include "SDL_rect.h"

constexpr int COLLIDE_INTERVAL = 4;

void collision::makeObjectMoveBounceWithRect(spriteMove::ObjectMoving& objectMove, const SpriteSize& objectSize, const SDL_Rect& rect)
{
	if( objectMove.get_x_position() + objectSize.w / 2 < rect.x + COLLIDE_INTERVAL && objectMove.get_x_norm() > 0 )
	{
		collision::checkYPosition(objectMove, objectSize, rect);
		objectMove.reverse_x_vector();
	}
	else if( objectMove.get_x_position() - objectSize.w / 2 >= rect.x + rect.w - COLLIDE_INTERVAL && objectMove.get_x_norm() < 0 )
	{
		collision::checkYPosition(objectMove, objectSize, rect);
		objectMove.reverse_x_vector();
	}
	else{
		collision::checkYPosition(objectMove, objectSize, rect);
	}
	objectMove.adjust_x_speed();
	objectMove.adjust_y_speed();
}

void collision::checkYPosition(spriteMove::ObjectMoving& objectMove, const SpriteSize& objectSize, const SDL_Rect& rect)
{
	if( objectMove.get_y_position() + objectSize.h / 2 < rect.y + COLLIDE_INTERVAL && objectMove.get_y_norm() > 0 )
	{
		objectMove.reverse_y_vector();
	}
	else if( objectMove.get_y_position() - objectSize.h / 2 >= rect.y + rect.h - COLLIDE_INTERVAL && objectMove.get_y_norm() < 0 )
	{
		objectMove.reverse_y_vector();
	}
}