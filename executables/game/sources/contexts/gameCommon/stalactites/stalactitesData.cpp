#include "contexts/gameCommon/stalactites/stalactitesData.h"
#include "generic/maths/orientation.h"
#include "customTypes/positionTypes.h"
#include "contexts/gameCommon/stalactites/stalactitesConsts.h"
#include "SDL_rect.h"
#include <cassert>

StalactiteData::StalactiteData(const Offset& position):
	move{position},
	startPosition{ position },
	trembleIndex{0},
	direction{stalactites::DefaultDirection},
	rumbleCount{0},
	state{ stalactites::StateStatic },
	length{ stalactites::DefaultLength }
{

}

StalactiteData::StalactiteData(const Offset& position, unsigned newDirection):
	move{position},
	startPosition{ position },
	trembleIndex{0},
	direction{newDirection},
	rumbleCount{0},
	state{ stalactites::StateStatic },
	length{ stalactites::DefaultLength }
{
	
}

void StalactiteData::rumble(const std::vector< int >& rumbleArray)
{
	if( stalactites::StateRumble == state )
	{
		assert( trembleIndex < rumbleArray.size() );
		move.set_x_position( move.get_x_position() + rumbleArray[trembleIndex] );
		incrementRumbleIndex(rumbleArray);
	}
}

void StalactiteData::incrementRumbleIndex(const std::vector< int >& rumbleArray)
{
	if( trembleIndex + 1 < rumbleArray.size() )
	{
		trembleIndex++;
	}
	else{
		trembleIndex = 0;
	}
	rumbleCount++;
}

void StalactiteData::startFallingIfRumbleEnds()
{
	if( stalactites::StateRumble == state )
	{
		if( stalactites::RumbleMax <= rumbleCount )
		{
			state = stalactites::StateFalling;
			move.setSpeed(stalactites::FallSpeed);
			move.setBothVectors( getDirectionVectors(stalactites::DirectionsNumber, direction, SQR_SIZE) );
			move.adjust_x_speed();
			move.adjust_y_speed();
			rumbleCount = 0;
		}
	}
}

void StalactiteData::resetStalactitePosition()
{
	move.setPosition(startPosition);
}

void StalactiteData::makeFalling()
{
	if( stalactites::StateFalling == state )
		move.moveObject();
}

unsigned StalactiteData::getDirection() const
{
	return direction;
}

Offset StalactiteData::getPosition() const
{
	return move.getOffsetPosition();
}

int StalactiteData::getXCoordinate() const
{
	return move.get_x_position();
}

int StalactiteData::getYCoordinate() const
{
	return move.get_y_position();
}

void StalactiteData::setState(unsigned newState)
{
	state = newState;
}

unsigned StalactiteData::getState() const
{
	return state;
}

bool StalactiteData::doesCollideWithRacket(const SDL_Rect& racketRect, const Offset& stalactiteTextureDimensions, const SDL_Rect& stalactiteRect) const
{
	return racketRect.x < move.get_x_position() - stalactiteTextureDimensions.x / 2 + stalactiteRect.x + stalactiteRect.w
		&& racketRect.x + racketRect.w >= move.get_x_position() - stalactiteTextureDimensions.x / 2 + stalactiteRect.x
		&& racketRect.y < move.get_y_position() - stalactiteTextureDimensions.y / 2 + stalactiteRect.y + stalactiteRect.h
		&& racketRect.y + racketRect.h >= move.get_y_position() - stalactiteTextureDimensions.y / 2 + stalactiteRect.y;
}