#include "contexts/duels/inGameObjects/balls/duelBall.h"
#include "contexts/gameCommon/rectCollisions/brickGridCollisions.h"
#include "contexts/duels/duelsConstexpr.h"

duels::ComboBallData::ComboBallData():
	move{},
	collision{}
{}

void duels::ComboBallData::bounceAgainstLeftOfScreen(int ballTextureWidth)
{
	if( move.get_x_norm() < 0 && move.get_x_position() < ballTextureWidth / 2 )
	{
		move.reverse_x_vector();
		move.adjust_x_speed();
	}
}

void duels::ComboBallData::bounceAgainstRightOfScreen(int ballTextureWidth)
{
	if( move.get_x_norm() > 0 && move.get_x_position() >= GameScreenWidth - ballTextureWidth / 2 )
	{
		move.reverse_x_vector();
		move.adjust_x_speed();
	}
}

void duels::ComboBallData::makeBallEffective(const Offset& newPosition, const Offset& newDirVector)
{
	move.setPosition(newPosition);
	move.setBothVectors(newDirVector);
	move.setSpeed(1);
	move.adjust_x_speed();
	move.adjust_y_speed();
	collision.resetAllCollisions();
}
