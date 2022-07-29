#include "spriteMove/spriteMoveData.h"
#include <cmath>

spriteMove::MovementThings::MovementThings(const Offset& startPos):
	moveSprite{startPos},
	vectorNumber{0},
	x_axis_way_accomp{false},
	y_axis_way_accomp{false},
	isWaiting{false},
	hasStarted{false},
	hasMoveEnded{false}
{

}

void spriteMove::MovementThings::addMoveInfoElement(int vect_x, int vect_y, int final_x_pos, int final_y_pos, double speed, std::chrono::milliseconds wait)
{
	vectMvtInfos.emplace_back( MoveInfo{Offset{vect_x, vect_y}, Offset{final_x_pos, final_y_pos}, speed, wait});
}

void spriteMove::MovementThings::initMoveToFirstVector()
{
	if( false == vectMvtInfos.empty() )
	{
		moveSprite.setBothVectors( vectMvtInfos[0].vectors );
		moveSprite.setSpeed( vectMvtInfos[0].speed );
		moveSprite.adjust_x_speed();
		moveSprite.adjust_y_speed();
		hasMoveEnded = false;
	}
}

void spriteMove::MovementThings::setStartPosition(int pos_x, int pos_y)
{
	moveSprite.setPosition( Offset{ pos_x, pos_y } );
}

void spriteMove::MovementThings::setToWaitingState()
{
	if( vectMvtInfos[vectorNumber].wait.count() > 0 )
	{	
		isWaiting = true;
		waitMeasure.joinTimePoints();
	}
	else{
		isWaiting = false;
	}
}

void spriteMove::MovementThings::waitingObserver()
{
	if( isWaiting )
	{
		if( waitMeasure.hasTimeElapsed( vectMvtInfos[vectorNumber].wait ) )
		{
			isWaiting = false;
		}
	}
}

void spriteMove::MovementThings::atLeastOneVectorInMove()
{
	setToWaitingState();
	vectorNumber++;
	moveSprite.setBothVectors( vectMvtInfos[vectorNumber].vectors );
	moveSprite.setSpeed( vectMvtInfos[vectorNumber].speed );
	moveSprite.adjust_x_speed();
	moveSprite.adjust_y_speed();
	x_axis_way_accomp = false;
	y_axis_way_accomp = false;
}

void spriteMove::MovementThings::move()
{
	waitingObserver();
	if( false == isWaiting )
	{
		moveSprite.moveObject();
	}
}

void spriteMove::MovementThings::setWayOnXaxisAccomplished(int increment)
{
	if( moveSprite.get_x_norm() < 0 && moveSprite.get_x_position() < vectMvtInfos[vectorNumber].finalPos.x + increment )
		x_axis_way_accomp = true;
	else if( moveSprite.get_x_norm() > 0 && moveSprite.get_x_position() > vectMvtInfos[vectorNumber].finalPos.x + increment )
		x_axis_way_accomp = true;
	else if( moveSprite.get_x_norm() == 0 )
		x_axis_way_accomp = true;
}

void spriteMove::MovementThings::setWayOnYaxisAccomplished(int increment)
{
	if( moveSprite.get_y_norm() < 0 && moveSprite.get_y_position() < vectMvtInfos[vectorNumber].finalPos.y + increment )
		y_axis_way_accomp = true;
	else if( moveSprite.get_y_norm() > 0 && moveSprite.get_y_position() > vectMvtInfos[vectorNumber].finalPos.y + increment )
		y_axis_way_accomp = true;
	else if( moveSprite.get_y_norm() == 0)
		y_axis_way_accomp = true;
}

double spriteMove::MovementThings::getAccuratePosX() const
{
	return moveSprite.getPosition().x;
}

double spriteMove::MovementThings::getAccuratePosY() const
{
	return moveSprite.getPosition().y;
}

int spriteMove::MovementThings::getXPos() const
{
	return moveSprite.get_x_position();
}

int spriteMove::MovementThings::getYPos() const
{
	return moveSprite.get_y_position();
}

const AccurCoords& spriteMove::MovementThings::getPosition() const
{
	return moveSprite.getPosition();
}

void spriteMove::MovementThings::resetMove(const Offset& startPos)
{
	moveSprite.setPosition(startPos);
	vectorNumber = 0;
	x_axis_way_accomp = false;
	y_axis_way_accomp = false;
	isWaiting = false;
	hasStarted = false;
	hasMoveEnded = false;
	initMoveToFirstVector();
}