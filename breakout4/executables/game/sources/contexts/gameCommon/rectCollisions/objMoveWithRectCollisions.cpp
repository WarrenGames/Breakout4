#include "contexts/gameCommon/rectCollisions/objMoveWithRectCollisions.h"
#include "spriteMove/objectMove.h"
#include "generic/sounds/soundHandler.h"
#include "types/spriteSize.h"
#include "consts/onePlayerLevelConsts.h"
#include "SDL_rect.h"

void rectCollision::startCollisionTest(spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval, const SoundHandler& sounds, unsigned soundIndex)
{
	if( rectCollision::doesAObjectCollideWithRect(objAMoving, objASize, objBRect) )
	{
		rectCollision::testTopCollision(objAMoving, objASize, objBRect, cornerInterval);
		rectCollision::testBottomCollision(objAMoving, objASize, objBRect, cornerInterval);
		rectCollision::testRightSideCollision(objAMoving, objASize, objBRect, cornerInterval);
		rectCollision::testLeftSideCollision(objAMoving, objASize, objBRect, cornerInterval);
		rectCollision::testTopLeftCornerCollision(objAMoving, objASize, objBRect, cornerInterval);
		rectCollision::testTopRightCornerCollision(objAMoving, objASize, objBRect, cornerInterval);
		rectCollision::testBottomLeftCornerCollision(objAMoving, objASize, objBRect, cornerInterval);
		rectCollision::testBottomRightCornerCollision(objAMoving, objASize, objBRect, cornerInterval);
		sounds.playSound(soundIndex);
	}
}

bool rectCollision::doesAObjectCollideWithRect(const spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect)
{
	return objAMoving.get_x_position() + objASize.w / 2 >= objBRect.x
		&& objAMoving.get_x_position() - objASize.w / 2 < objBRect.x + objBRect.w
		&& objAMoving.get_y_position() + objASize.h / 2 >= objBRect.y
		&& objAMoving.get_y_position() - objASize.h / 2 < objBRect.y + objBRect.h;
}

void rectCollision::testTopCollision(spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval)
{
	if( 	objAMoving.get_y_norm() > 0 
		&&	rectCollision::isNearTopSide(objAMoving, objASize, objBRect)
		&& 	objAMoving.get_x_position() + objASize.w / 2 - cornerInterval >= objBRect.x 
		&& 	objAMoving.get_x_position() - objASize.w / 2 + cornerInterval < objBRect.x + objBRect.w )
	{
		objAMoving.reverse_y_vector();
		objAMoving.adjust_y_speed();
	}
}

void rectCollision::testBottomCollision(spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval)
{
	if(		objAMoving.get_y_norm() < 0 
		&& 	rectCollision::isNearBottomSide(objAMoving, objASize, objBRect)
		&& 	objAMoving.get_x_position() + objASize.w / 2 - cornerInterval >= objBRect.x 
		&& 	objAMoving.get_x_position() - objASize.w / 2 + cornerInterval < objBRect.x + objBRect.w )
	{
		objAMoving.reverse_y_vector();
		objAMoving.adjust_y_speed();
	}
}

void rectCollision::testRightSideCollision(spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval)
{
	if( 	objAMoving.get_x_norm() < 0 
		&& 	rectCollision::isNearRightSide(objAMoving, objASize, objBRect)
		&&	objAMoving.get_y_position() + objASize.h / 2 - cornerInterval >= objBRect.y
		&& 	objAMoving.get_y_position() - objASize.h / 2 + cornerInterval < objBRect.y + objBRect.h )
	{
		objAMoving.reverse_x_vector();
		objAMoving.adjust_x_speed();
	}
}

void rectCollision::testLeftSideCollision(spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval)
{
	if( 	objAMoving.get_x_norm() > 0
		&& 	rectCollision::isNearLeftSide(objAMoving, objASize, objBRect)
		&&	objAMoving.get_y_position() + objASize.h / 2 - cornerInterval >= objBRect.y
		&& 	objAMoving.get_y_position() - objASize.h / 2 + cornerInterval < objBRect.y + objBRect.h )
	{
		objAMoving.reverse_x_vector();
		objAMoving.adjust_x_speed();
	}
}

void rectCollision::testTopLeftCornerCollision(spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval)
{
	if( 	objAMoving.get_x_norm() > 0 && objAMoving.get_y_norm() > 0 
		&& rectCollision::isNearTopSide(objAMoving, objASize, objBRect)
		&& rectCollision::isNearLeftSide(objAMoving, objASize, objBRect)
		&&	objAMoving.get_x_position() + objASize.w / 2 - cornerInterval < objBRect.x 
		&& 	objAMoving.get_y_position() + objASize.h / 2 - cornerInterval < objBRect.y )
	{
		giveObjectNewDirection(objAMoving, Offset{-1, -1} );
	}
}

void rectCollision::testTopRightCornerCollision(spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval)
{
	if( 	objAMoving.get_x_norm() < 0 && objAMoving.get_y_norm() > 0 
		&& rectCollision::isNearTopSide(objAMoving, objASize, objBRect)
		&& rectCollision::isNearRightSide(objAMoving, objASize, objBRect)
		&&	objAMoving.get_x_position() - objASize.w / 2 + cornerInterval >= objBRect.x + objBRect.w 
		&&	objAMoving.get_y_position() - objASize.h / 2 + cornerInterval >= objBRect.y )
	{
		giveObjectNewDirection(objAMoving, Offset{1, -1} );
	}
}

void rectCollision::testBottomLeftCornerCollision(spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval)
{
	if( 	objAMoving.get_x_norm() > 0 && objAMoving.get_y_norm() < 0 
		&& rectCollision::isNearBottomSide(objAMoving, objASize, objBRect)
		&& rectCollision::isNearLeftSide(objAMoving, objASize, objBRect)
		&&	objAMoving.get_x_position() + objASize.w / 2 - cornerInterval < objBRect.x 
		&& 	objAMoving.get_y_position() - objASize.h / 2 + cornerInterval >= objBRect.y + objBRect.h )
	{
		giveObjectNewDirection(objAMoving, Offset{-1, 1} );
	}
}

void rectCollision::testBottomRightCornerCollision(spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect, int cornerInterval)
{
	if( 	objAMoving.get_x_norm() < 0 && objAMoving.get_y_norm() < 0
		&& rectCollision::isNearBottomSide(objAMoving, objASize, objBRect)
		&& rectCollision::isNearRightSide(objAMoving, objASize, objBRect)
		&& 	objAMoving.get_x_position() - objASize.w / 2 + cornerInterval >= objBRect.x + objBRect.w
		&& 	objAMoving.get_y_position() - objASize.h / 2 + cornerInterval >= objBRect.y + objBRect.h )
	{
		giveObjectNewDirection(objAMoving, Offset{1, 1} );
	}
}

bool rectCollision::isNearTopSide(const spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect)
{
	return objAMoving.get_y_position() + objASize.h / 2 - objBRect.h / 2 < objBRect.y;
}

bool rectCollision::isNearBottomSide(const spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect)
{
	return objAMoving.get_y_position() - objASize.h / 2 + objBRect.h / 2 >= objBRect.y + objBRect.h;
}

bool rectCollision::isNearLeftSide(const spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect)
{
	return objAMoving.get_x_position() + objASize.w / 2 - objBRect.w / 2 < objBRect.x;
}

bool rectCollision::isNearRightSide(const spriteMove::ObjectMoving& objAMoving, const SpriteSize& objASize, const SDL_Rect& objBRect)
{
	return objAMoving.get_x_position() - objASize.w / 2 + objBRect.w / 2 >= objBRect.x + objBRect.w;
}
