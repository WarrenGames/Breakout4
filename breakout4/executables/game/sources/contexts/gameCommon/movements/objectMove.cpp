#include "contexts/gameCommon/movements/objectMove.h"
#include "consts/constexprScreen.h"
#include <cmath>

ObjectMoving::ObjectMoving():
	position{},
	on_axis_speed{},
	globalSpeed{0},
	dirVectors{0, 0}
{

}

ObjectMoving::ObjectMoving(const Offset& startingPosition):
	position{startingPosition},
	globalSpeed{0},
	dirVectors{0, 0}
{

}

ObjectMoving::ObjectMoving(const AccurCoords& startCoords, double newSpeed, const Offset& newDirVectors):
	position{startCoords},
	on_axis_speed{},
	globalSpeed{newSpeed},
	dirVectors{newDirVectors}
{
	adjust_x_speed();
	adjust_y_speed();
}

void ObjectMoving::adjust_x_speed()
{
	if( !( dirVectors.x == 0 && dirVectors.y == 0 ) )
	{
		on_axis_speed.x = std::sqrt( SQR_POW( dirVectors.x ) * SQR_POW( globalSpeed) / ( SQR_POW( dirVectors.x ) + SQR_POW( dirVectors.y) ) );
		if( dirVectors.x < 0 )
			on_axis_speed.x = -on_axis_speed.x;
	}
	else
		on_axis_speed.x = 0;
}

void ObjectMoving::adjust_y_speed()
{
	if( !( dirVectors.x == 0 && dirVectors.y == 0 ) )
	{
		on_axis_speed.y = std::sqrt( SQR_POW( dirVectors.y ) * SQR_POW( globalSpeed) / ( SQR_POW( dirVectors.x ) + SQR_POW( dirVectors.y) ) );
		if( dirVectors.y < 0 )
			on_axis_speed.y = -on_axis_speed.y;
	}
	else
		on_axis_speed.y = 0;
}

void ObjectMoving::set_x_vector(int new_x_norm)
{
	dirVectors.x = new_x_norm;
}

void ObjectMoving::set_y_vector(int new_y_norm)
{
	dirVectors.y = new_y_norm;
}

void ObjectMoving::setBothVectors(const Offset& newVectors)
{
	dirVectors = newVectors;
}

void ObjectMoving::setSpeed(double newGlobalSpeed)
{
	globalSpeed = newGlobalSpeed;
}

void ObjectMoving::incrementSpeed(double increment)
{
	globalSpeed += increment;
}

double ObjectMoving::getSpeed() const
{
	return globalSpeed;
}

int ObjectMoving::get_x_position() const
{
	return static_cast<int>(position.x);
}

int ObjectMoving::get_y_position() const
{
	return static_cast<int>(position.y);
}

const AccurCoords& ObjectMoving::getPosition() const
{
	return position;
}

Offset ObjectMoving::getOffsetPosition() const
{
	return Offset{ static_cast<int>(position.x), static_cast<int>(position.y) };
}

int ObjectMoving::get_x_norm() const
{
	return dirVectors.x;
}

int ObjectMoving::get_y_norm() const
{
	return dirVectors.y;
}

void ObjectMoving::reverse_x_vector()
{
	dirVectors.x *= -1;
}

void ObjectMoving::reverse_y_vector()
{
	dirVectors.y *= -1;
}

void ObjectMoving::moveObject()
{
	position.x += on_axis_speed.x;
	position.y += on_axis_speed.y;
}

void ObjectMoving::setPosition(const Offset& newPosition)
{
	position = newPosition;
}

void ObjectMoving::set_x_position(double new_x_position)
{
	position.x = new_x_position;
}

void ObjectMoving::set_y_position(double new_y_position)
{
	position.y = new_y_position;
}

void ObjectMoving::orientToAGivenObject(const ObjectMoving& distantObject)
{
	dirVectors.x = distantObject.get_x_position() - static_cast<int>(position.x);
	dirVectors.y = distantObject.get_y_position() - static_cast<int>(position.y);
	adjust_x_speed();
	adjust_y_speed();
}

void ObjectMoving::stopObject()
{
	on_axis_speed.x = 0;
	on_axis_speed.y = 0;
}

void giveObjectNewDirection(ObjectMoving& move, const Offset& newOffset)
{
	move.setBothVectors(newOffset);
	move.adjust_x_speed();
	move.adjust_y_speed();
}
