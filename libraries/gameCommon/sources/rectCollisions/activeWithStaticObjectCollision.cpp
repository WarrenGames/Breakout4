#include "rectCollisions/activeWithStaticObjectCollision.h"
#include "spriteMove/objectMove.h"
#include "SDL_rect.h"

bool collision::activeAndStatic::isThereCollision(const spriteMove::ObjectMoving& moveA, const SDL_Rect& rectA, const SDL_Rect& rectB, int interval)
{
	return moveA.get_x_position() + rectA.x + rectA.w >= rectB.x - interval
		&& moveA.get_x_position() + rectA.x < rectB.x + rectB.w + interval
		&& moveA.get_y_position() + rectA.y + rectA.h >= rectB.y - interval
		&& moveA.get_y_position() + rectA.y < rectB.y + rectB.h + interval;
}

void collision::activeAndStatic::processBouncing(spriteMove::ObjectMoving& moveA, const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	if( collision::activeAndStatic::isThereCollision(moveA, rectA, rectB, 0) )
	{
		collision::activeAndStatic::bouncingOntoNorth(moveA, rectA, rectB);
		collision::activeAndStatic::bouncingOntoSouth(moveA, rectA, rectB);
		collision::activeAndStatic::bouncingOntoWest(moveA, rectA, rectB);
		collision::activeAndStatic::bouncingOntoEast(moveA, rectA, rectB);
	}
}

void collision::activeAndStatic::bouncingOntoNorth(spriteMove::ObjectMoving& moveA, const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	if( moveA.get_y_norm() > 0 && moveA.get_y_position() + rectA.y + rectA.h >= rectB.y && moveA.get_y_position() + rectA.y + rectA.h < rectB.y + rectB.h / 2 )
	{
		moveA.reverse_y_vector();
		moveA.adjust_y_speed();
	}
}

void collision::activeAndStatic::bouncingOntoSouth(spriteMove::ObjectMoving& moveA, const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	if( moveA.get_y_norm() < 0 && moveA.get_y_position() + rectA.y < rectB.y + rectB.h && moveA.get_y_position() + rectA.y > rectB.y + rectB.h / 2 )
	{
		moveA.reverse_y_vector();
		moveA.adjust_y_speed();
	}
}

void collision::activeAndStatic::bouncingOntoWest(spriteMove::ObjectMoving& moveA, const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	if( moveA.get_x_norm() > 0 && moveA.get_x_position() + rectA.x + rectA.w >= rectB.x && moveA.get_x_position() + rectA.x + rectA.w < rectB.x + rectB.w / 2 )
	{
		moveA.reverse_x_vector();
		moveA.adjust_x_speed();
	}
}

void collision::activeAndStatic::bouncingOntoEast(spriteMove::ObjectMoving& moveA, const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	if( moveA.get_x_norm() < 0 && moveA.get_x_position() + rectA.x < rectB.x + rectB.w && moveA.get_x_position() + rectA.x > rectB.x + rectB.w / 2 )
	{
		moveA.reverse_x_vector();
		moveA.adjust_x_speed();
	}
}