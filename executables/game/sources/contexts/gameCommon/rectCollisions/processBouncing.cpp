#include "contexts/gameCommon/rectCollisions/processBouncing.h"
#include "spriteMove/objectMove.h"
#include "customTypes/positionTypes.h"
#include "types/spriteSize.h"

bool bouncing::objectsCollide(const spriteMove::ObjectMoving& moveA, const SpriteSize& objAsize, const spriteMove::ObjectMoving& moveB, const SpriteSize& objBsize, int interval)
{
	return 	   moveA.get_x_position() + objAsize.w / 2  >= moveB.get_x_position() - objBsize.w / 2  - interval
			&& moveA.get_x_position() - objAsize.w / 2  <  moveB.get_x_position() + objBsize.w / 2  + interval
			&& moveA.get_y_position() + objAsize.h / 2 >= moveB.get_y_position() - objBsize.h / 2 - interval
			&& moveA.get_y_position() - objAsize.h / 2 <  moveB.get_y_position() + objBsize.h / 2 + interval;
}

void bouncing::processElementsBouncing(spriteMove::ObjectMoving& objAmove, spriteMove::ObjectMoving& objBmove, const SpriteSize& objBsize)
{
	if( objAmove.get_x_position() < objBmove.get_x_position() - objBsize.w / 2 )
	{
		bouncing::objA_isToLeftOfObjB(objAmove, objBmove, objBsize);
	}
	else if( objAmove.get_x_position() > objBmove.get_x_position() + objBsize.w / 2 )
	{
		bouncing::objA_isToRightOfObjB(objAmove, objBmove, objBsize);
	}
	else{
		bouncing::objA_notOnLeftOrRightOfB_obj(objAmove, objBmove);
	}
}

void bouncing::objA_isToLeftOfObjB(spriteMove::ObjectMoving& objAmove, spriteMove::ObjectMoving& objBmove, const SpriteSize& Bsize)
{
	//Bounce on the top left
	if( objAmove.get_y_position() < objBmove.get_y_position() - Bsize.h / 2 )
	{
		giveObjectNewDirection(objAmove, Offset{-1, -1});
		giveObjectNewDirection(objBmove, Offset{1, 1});
	}
	//Bounce on the bottom left
	else if( objAmove.get_y_position() > objBmove.get_y_position() + Bsize.h / 2 )
	{
		giveObjectNewDirection(objAmove, Offset{-1, 1});
		giveObjectNewDirection(objBmove, Offset{1, -1});
	}
	else{
		bouncing::objAbouncesOnB_left(objAmove, objBmove);
	}
}

void bouncing::objAbouncesOnB_left(spriteMove::ObjectMoving& objAmove, spriteMove::ObjectMoving& objBmove)
{
	if( objAmove.get_x_norm() > 0 )
	{
		objAmove.reverse_x_vector();
		objAmove.adjust_x_speed();
	}
	if( objBmove.get_x_norm() < 0 )
	{
		objBmove.reverse_x_vector();
		objBmove.adjust_x_speed();
	}
}

void bouncing::objA_isToRightOfObjB(spriteMove::ObjectMoving& objAmove, spriteMove::ObjectMoving& objBmove, const SpriteSize& Bsize)
{
	//Bounce on the top right
	if( objAmove.get_y_position() < objBmove.get_y_position() - Bsize.h / 2 )
	{
		giveObjectNewDirection(objAmove, Offset{1, -1});
		giveObjectNewDirection(objBmove, Offset{-1, 1});
	}
	//Bounce ont the bottom right
	else if( objAmove.get_y_position() > objBmove.get_y_position() + Bsize.h / 2 )
	{
		giveObjectNewDirection(objAmove, Offset{1, 1}); 
		giveObjectNewDirection(objBmove, Offset{-1, -1,});
	}
	//Bounce on the right
	else{
		bouncing::objA_bouncesOnB_right(objAmove, objBmove);
	}
}

void bouncing::objA_bouncesOnB_right(spriteMove::ObjectMoving& objAmove, spriteMove::ObjectMoving& objBmove)
{
	if( objAmove.get_x_norm() < 0 )
	{
		objAmove.reverse_x_vector();
		objAmove.adjust_x_speed();
	}
	if( objBmove.get_x_norm() > 0 )
	{
		objBmove.reverse_x_vector();
		objBmove.adjust_x_speed();
	}
}

void bouncing::objA_notOnLeftOrRightOfB_obj(spriteMove::ObjectMoving& objAmove, spriteMove::ObjectMoving& objBmove)
{
	//Bounce on the top of coin
	if( objAmove.get_y_position() < objBmove.get_y_position() )
	{
		if( objAmove.get_y_norm() > 0 ){
			objAmove.reverse_y_vector();
			objAmove.adjust_y_speed();
		}
		if( objBmove.get_y_norm() < 0 ){
			objBmove.reverse_y_vector();
			objBmove.adjust_y_speed();
		}
	}
	//Bounce on the bottom of coin
	else{
		if( objAmove.get_y_norm() < 0 ){
			objAmove.reverse_y_vector();
			objAmove.adjust_y_speed();
		}
		if( objBmove.get_y_norm() > 0 ){
			objBmove.reverse_y_vector();
			objBmove.adjust_y_speed();
		}
	}
}
