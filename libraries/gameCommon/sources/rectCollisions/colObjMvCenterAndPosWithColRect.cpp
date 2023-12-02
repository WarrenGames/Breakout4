#include "rectCollisions/colObjMvCenterAndPosWithColRect.h"
#include "spriteMove/objectMove.h"
#include "types/spriteSize.h"
#include "SDL_rect.h"

bool collision::objMvAndSingleColRect::doCollide(const spriteMove::ObjectMoving& moveA, const SpriteSize& aSize, const spriteMove::ObjectMoving& moveB, const SDL_Rect& bCollideRect, 
													int interval)
{
	return moveA.get_x_position() + aSize.w / 2 >= moveB.get_x_position() + bCollideRect.x - interval
		&& moveA.get_x_position() - aSize.w / 2 < moveB.get_x_position() + bCollideRect.x + bCollideRect.w + interval
		&& moveA.get_y_position() + aSize.h / 2 >= moveB.get_y_position() + bCollideRect.y - interval
		&& moveA.get_y_position() - aSize.h / 2 < moveB.get_y_position() + bCollideRect.y + bCollideRect.h + interval;
}

void collision::objMvAndSingleColRect::processBouncing(spriteMove::ObjectMoving& moveA, spriteMove::ObjectMoving& moveB, const SDL_Rect& bCollideRect)
{
	if( collision::objMvAndSingleColRect::isOnX_a_before_b(moveA, moveB, bCollideRect) )
	{
		if( collision::objMvAndSingleColRect::isOnY_a_before_b(moveA, moveB, bCollideRect) )
		{
			spriteMove::giveObjectNewDirection(moveA, Offset{ -1, -1 } );
			spriteMove::giveObjectNewDirection(moveB, Offset{ 1, 1 } );
			
		}
		else if( collision::objMvAndSingleColRect::isOnY_a_on_b(moveA, moveB, bCollideRect) )
		{
			collision::objMvAndSingleColRect::horizontalBouncing(moveA, moveB);
		}
		else if( collision::objMvAndSingleColRect::isOnY_a_after_b(moveA, moveB, bCollideRect) )
		{
			spriteMove::giveObjectNewDirection(moveA, Offset{ -1, 1 } );
			spriteMove::giveObjectNewDirection(moveB, Offset{ 1, -1 } );
		}
	}
	else if( collision::objMvAndSingleColRect::isOnX_a_on_b(moveA, moveB, bCollideRect) )
	{
		if( collision::objMvAndSingleColRect::isOnY_a_before_b(moveA, moveB, bCollideRect) )
		{
			collision::objMvAndSingleColRect::verticalBouncing(moveA, moveB);
		}
		else if( collision::objMvAndSingleColRect::isOnY_a_on_b(moveA, moveB, bCollideRect) )
		{
			collision::objMvAndSingleColRect::verticalBouncing(moveA, moveB);
			collision::objMvAndSingleColRect::horizontalBouncing(moveA, moveB);
			
		}
		else if( collision::objMvAndSingleColRect::isOnY_a_after_b(moveA, moveB, bCollideRect) )
		{
			collision::objMvAndSingleColRect::verticalBouncing(moveA, moveB);
		}
	}
	else if( collision::objMvAndSingleColRect::isOnX_a_after_b(moveA, moveB, bCollideRect) )
	{
		if( collision::objMvAndSingleColRect::isOnY_a_before_b(moveA, moveB, bCollideRect) )
		{
			spriteMove::giveObjectNewDirection(moveA, Offset{ 1, -1 } );
			spriteMove::giveObjectNewDirection(moveB, Offset{ -1, 1 } );
		}
		else if( collision::objMvAndSingleColRect::isOnY_a_on_b(moveA, moveB, bCollideRect) )
		{
			collision::objMvAndSingleColRect::horizontalBouncing(moveA, moveB);
		}
		else if( collision::objMvAndSingleColRect::isOnY_a_after_b(moveA, moveB, bCollideRect) )
		{
			spriteMove::giveObjectNewDirection(moveA, Offset{ 1, 1 } );
			spriteMove::giveObjectNewDirection(moveB, Offset{ -1, -1 } );
		}
	}
}

void collision::objMvAndSingleColRect::verticalBouncing(spriteMove::ObjectMoving& moveA, spriteMove::ObjectMoving& moveB)
{
	moveA.reverse_y_vector();
	moveA.adjust_y_speed();
	moveB.reverse_y_vector();
	moveB.adjust_y_speed();
}

void collision::objMvAndSingleColRect::horizontalBouncing(spriteMove::ObjectMoving& moveA, spriteMove::ObjectMoving& moveB)
{
	moveA.reverse_x_vector();
	moveA.adjust_x_speed();
	moveB.reverse_x_vector();
	moveB.adjust_x_speed();
}

bool collision::objMvAndSingleColRect::isOnX_a_before_b(spriteMove::ObjectMoving& moveA, spriteMove::ObjectMoving& moveB, const SDL_Rect& bCollideRect)
{
	return moveA.get_x_position() < moveB.get_x_position() + bCollideRect.x;
}

bool collision::objMvAndSingleColRect::isOnX_a_on_b(spriteMove::ObjectMoving& moveA, spriteMove::ObjectMoving& moveB, const SDL_Rect& bCollideRect)
{
	return moveA.get_x_position() >= moveB.get_x_position() + bCollideRect.x 
		&& moveA.get_x_position() < moveB.get_x_position() + bCollideRect.x + bCollideRect.w;
}

bool collision::objMvAndSingleColRect::isOnX_a_after_b(spriteMove::ObjectMoving& moveA, spriteMove::ObjectMoving& moveB, const SDL_Rect& bCollideRect)
{
	return moveA.get_x_position() >= moveB.get_x_position() + bCollideRect.x + bCollideRect.w;
}

bool collision::objMvAndSingleColRect::isOnY_a_before_b(spriteMove::ObjectMoving& moveA, spriteMove::ObjectMoving& moveB, const SDL_Rect& bCollideRect)
{
	return moveA.get_y_position() < moveB.get_y_position() + bCollideRect.y;
}

bool collision::objMvAndSingleColRect::isOnY_a_on_b(spriteMove::ObjectMoving& moveA, spriteMove::ObjectMoving& moveB, const SDL_Rect& bCollideRect)
{
	return moveA.get_y_position() >= moveB.get_y_position() + bCollideRect.y 
		&& moveA.get_y_position() < moveB.get_y_position() + bCollideRect.y + bCollideRect.h;
}

bool collision::objMvAndSingleColRect::isOnY_a_after_b(spriteMove::ObjectMoving& moveA, spriteMove::ObjectMoving& moveB, const SDL_Rect& bCollideRect)
{
	return moveA.get_y_position() >= moveB.get_y_position() + bCollideRect.y + bCollideRect.h;
}