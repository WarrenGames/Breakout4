#include "spriteMove/objectMove.h"
#include <cmath>

spriteMove::ObjectMoving::ObjectMoving():
	position{},
	on_axis_speed{},
	globalSpeed{0},
	dirVectors{0, 0}
{

}

spriteMove::ObjectMoving::ObjectMoving(const Offset& startingPosition):
	position{startingPosition},
	globalSpeed{0},
	dirVectors{0, 0}
{

}

spriteMove::ObjectMoving::ObjectMoving(const AccurCoords& startCoords, double newSpeed, const Offset& newDirVectors):
	position{startCoords},
	on_axis_speed{},
	globalSpeed{newSpeed},
	dirVectors{newDirVectors}
{
	adjust_x_speed();
	adjust_y_speed();
}

void spriteMove::ObjectMoving::adjust_x_speed()
{
	if( !( dirVectors.x == 0 && dirVectors.y == 0 ) )
	{
		on_axis_speed.x = dirVectors.x * globalSpeed / std::sqrt( dirVectors.x * dirVectors.x  + dirVectors.y * dirVectors.y );
	}
	else{
		on_axis_speed.x = 0;
	}
}

void spriteMove::ObjectMoving::adjust_y_speed()
{
	if( !( dirVectors.x == 0 && dirVectors.y == 0 ) )
	{
		on_axis_speed.y = dirVectors.y * globalSpeed / std::sqrt( dirVectors.x * dirVectors.x + dirVectors.y * dirVectors.y );
	}
	else{
		on_axis_speed.y = 0;
	}
}

void spriteMove::ObjectMoving::set_x_vector(int new_x_norm)
{
	dirVectors.x = new_x_norm;
}

void spriteMove::ObjectMoving::set_y_vector(int new_y_norm)
{
	dirVectors.y = new_y_norm;
}

void spriteMove::ObjectMoving::setBothVectors(const Offset& newVectors)
{
	dirVectors = newVectors;
}

void spriteMove::ObjectMoving::setSpeed(double newGlobalSpeed)
{
	globalSpeed = newGlobalSpeed;
}

void spriteMove::ObjectMoving::incrementSpeed(double increment)
{
	globalSpeed += increment;
}

double spriteMove::ObjectMoving::getSpeed() const
{
	return globalSpeed;
}

int spriteMove::ObjectMoving::get_x_position() const
{
	return static_cast<int>(position.x);
}

int spriteMove::ObjectMoving::get_y_position() const
{
	return static_cast<int>(position.y);
}

const AccurCoords& spriteMove::ObjectMoving::getPosition() const
{
	return position;
}

Offset spriteMove::ObjectMoving::getOffsetPosition() const
{
	return Offset{ static_cast<int>(position.x), static_cast<int>(position.y) };
}

int spriteMove::ObjectMoving::get_x_norm() const
{
	return dirVectors.x;
}

int spriteMove::ObjectMoving::get_y_norm() const
{
	return dirVectors.y;
}

void spriteMove::ObjectMoving::reverse_x_vector()
{
	dirVectors.x *= -1;
}

void spriteMove::ObjectMoving::reverse_y_vector()
{
	dirVectors.y *= -1;
}

void spriteMove::ObjectMoving::moveObject()
{
	position.x += on_axis_speed.x;
	position.y += on_axis_speed.y;
}

void spriteMove::ObjectMoving::setPosition(const Offset& newPosition)
{
	position = newPosition;
}

void spriteMove::ObjectMoving::setPosition(const AccurCoords& newPosition)
{
	position = newPosition;
}

void spriteMove::ObjectMoving::add_to_xpos(double x_add)
{
	position.x += x_add;
}

void spriteMove::ObjectMoving::add_to_ypos(double y_add)
{
	position.y += y_add;
}

void spriteMove::ObjectMoving::set_x_position(double new_x_position)
{
	position.x = new_x_position;
}

void spriteMove::ObjectMoving::set_y_position(double new_y_position)
{
	position.y = new_y_position;
}

void spriteMove::ObjectMoving::orientToAGivenObject(const ObjectMoving& distantObject)
{
	dirVectors.x = distantObject.get_x_position() - static_cast<int>(position.x);
	dirVectors.y = distantObject.get_y_position() - static_cast<int>(position.y);
	adjust_x_speed();
	adjust_y_speed();
}

void spriteMove::ObjectMoving::stopObject()
{
	on_axis_speed.x = 0;
	on_axis_speed.y = 0;
}

void spriteMove::giveObjectNewDirection(ObjectMoving& move, const Offset& newOffset)
{
	move.setBothVectors(newOffset);
	move.adjust_x_speed();
	move.adjust_y_speed();
}
