#include "contexts/duels/inGameObjects/bonusCoins/bonusCoin.h"
#include "consts/constexprScreen.h"
#include "contexts/duels/duelsConstexpr.h"

duels::ComboCoinData::ComboCoinData():
	move{},
	animIndex{0},
	collision{}
{}

void duels::ComboCoinData::bounceAgainstLeftOfScreen()
{
	if( move.get_x_norm() < 0 && move.get_x_position() - CoinTextureSize / 2 <= 0 ) 
	{
		move.reverse_x_vector();
		move.adjust_x_speed();
	}
}

void duels::ComboCoinData::bounceAgainstRightOfScreen()
{
	if( move.get_x_norm() > 0 && move.get_x_position() + CoinTextureSize / 2 > GameScreenWidth )
	{
		move.reverse_x_vector();
		move.adjust_x_speed();
	}
}

void duels::ComboCoinData::animateCoin()
{
	if( animIndex < duels::CoinFramesNumber - 1 )
		animIndex++;
	else
		animIndex = 0;
}

void duels::ComboCoinData::moveCoin()
{
	move.moveObject();
}

void duels::ComboCoinData::makeCoinEffective(const Offset& newPosition, const Offset& newDirVector)
{
	move.setPosition(newPosition);
	move.setBothVectors(newDirVector);
	move.setSpeed(1);
	move.adjust_x_speed();
	move.adjust_y_speed();
	collision.resetAllCollisions();
}