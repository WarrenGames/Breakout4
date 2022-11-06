#include "contexts/gameCommon/rackets/racketData.h"
#include "contexts/gameCommon/rackets/racketDrawer.h"
#include "contexts/duels/duelsConstexpr.h"
#include "consts/onePlayerLevelConsts.h"
#include <cassert>

RacketData::RacketData(unsigned startSize, double startSpeed, int start_y_position):
	isFreezed{false},
	freezeDuration{0},
	speed{startSpeed},
	center_x_position{ GameScreenWidth / 2 },
	racketSize{startSize},
	top_y_position{ start_y_position},
	moveTime{},
	freezeTime{}
{
	assert( startSize < duels::RacketMax );
}

void RacketData::moveRacket(unsigned moveDirection, int racketCurrentWidth)
{
	assert( ( moveDirection == MoveToLeft || moveDirection == MoveToRight ) && "Error: bad parameter in raquette's move function" );
	if( false == isFreezed )
	{
		if( moveTime.hasTimeElapsed( std::chrono::milliseconds{10} ) )
		{
			if( moveDirection == MoveToLeft )
				moveToLeft(racketCurrentWidth);
			else if( moveDirection == MoveToRight ){
				moveToRight(racketCurrentWidth);
			}
			moveTime.joinTimePoints();
		}
	}
}

void RacketData::moveToLeft(int racketCurrentWidth)
{
	if( center_x_position > racketCurrentWidth / 2 )
		center_x_position -= speed;
	else{
		center_x_position = racketCurrentWidth / 2;
	}
}

void RacketData::moveToRight(int racketCurrentWidth)
{
	if( center_x_position + racketCurrentWidth / 2 < GameScreenWidth )
		center_x_position += speed;
	else
		center_x_position = GameScreenWidth - racketCurrentWidth / 2;
}

void RacketData::modifySize(int addToSize)
{
	racketSize += addToSize;
}

bool RacketData::canBeEnlarged() const
{
	return racketSize < onePlGame::BigRacket;
}

void RacketData::enlarge()
{
	racketSize += 1;
}
	
unsigned RacketData::getSize() const
{
	return racketSize;
}

double RacketData::getSpeed() const
{
	return speed;
}

void RacketData::addToSpeed(double speedToAdd)
{
	speed += speedToAdd;
}

bool RacketData::canSpeedUp() const
{
	return speed < onePlGame::RacketMaxSpeed;
}

int RacketData::get_x_pos() const
{
	return static_cast<int>(center_x_position);
}

int RacketData::get_y_pos() const
{
	return top_y_position;
}

bool RacketData::canBeFreezed() const
{
	return isFreezed == false;
}

bool RacketData::isRacketFreezed() const
{
	return isFreezed;
}

void RacketData::startFreeze(std::chrono::milliseconds newFreezeDuration)
{
	isFreezed = true;
	freezeTime.joinTimePoints();
	freezeDuration = newFreezeDuration;
}

void RacketData::unfreezeIfPossible()
{
	if( isFreezed && freezeTime.hasTimeElapsed( freezeDuration ) )
	{
		isFreezed = false;
		freezeTime.joinTimePoints();
	}
}