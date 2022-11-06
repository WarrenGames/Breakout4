#include "contexts/gameCommon/halloween/bat/badBatData.h"
#include "consts/constexprScreen.h"
#include <cassert>

BadBatData::BadBatData():
	wingsFrameNumber{0},
	batMove{AccurCoords{-SQR_SIZE*5, GameScreenHeight + SQR_SIZE *4}, 0, Offset{1, 0}},
	wingsAnim{},
	batMoveDelay{},
	faceIndex{bat::FaceEffort},
	moveState{bat::MoveOff},
	wingsMoveDown{true},
	wingsOffsets{{ {4, 30}, {4, 26}, {4, 23}, {5, 19}, {5, 14} }}
{

}

void BadBatData::update()
{
	animation();
	moveBat();
	stopBat();
}

void BadBatData::changeMovementType(unsigned newMoveState, const Offset& newVectors)
{
	assert( newMoveState <= bat::MoveFromLeft );
	moveState = newMoveState;
	batMove.setBothVectors(newVectors);
	batMove.adjust_x_speed();
	batMove.adjust_y_speed();
}

void BadBatData::changeFace(std::size_t newFace)
{
	assert( newFace < bat::FaceMax );
	faceIndex = newFace;
}

const Offset& BadBatData::getOffset() const
{
	assert( wingsFrameNumber < wingsOffsets.size() );
	return wingsOffsets[wingsFrameNumber];
}

unsigned BadBatData::getMoveState() const
{
	return moveState;
}

void BadBatData::startBadBatActivity()
{
	moveState = bat::MoveFromLeft;
	batMove.setPosition(Offset{-SQR_SIZE*4, GameScreenHeight - SQR_SIZE*4});
	batMove.setSpeed(2);
	giveObjectNewDirection(batMove, Offset{1, 0} );
}

const AccurCoords& BadBatData::getBatPosition() const
{
	return batMove.getPosition();
}

void BadBatData::animation()
{
	if( wingsAnim.hasTimeElapsed( std::chrono::milliseconds{100} ) )
	{
		if( wingsMoveDown )
		{
			if( wingsFrameNumber + 1 < bat::WingImagesNumber )
				wingsFrameNumber++;
			else{
				wingsFrameNumber--;
				wingsMoveDown = false;
			}
		}
		else{
			if( wingsFrameNumber > 0 )
				wingsFrameNumber--;
			else{
				wingsFrameNumber++;
				wingsMoveDown = true;
			}
		}
		wingsAnim.joinTimePoints();
	}
}

void BadBatData::moveBat()
{
	if( batMoveDelay.hasTimeElapsed( std::chrono::milliseconds{10} ) && (moveState == bat::MoveFromLeft || moveState == bat::MoveFromRight) )
	{
		batMove.moveObject();
		batMoveDelay.joinTimePoints();
	}
}

void BadBatData::stopBat()
{
	if( 	(moveState == bat::MoveFromLeft && batMove.getPosition().x >= GameScreenWidth + SQR_SIZE *3 )
		||	(moveState == bat::MoveFromRight && batMove.getPosition().x <= -SQR_SIZE * 3 ) )
	{
		batMove.setSpeed(0);
		batMove.adjust_x_speed();
		batMove.adjust_y_speed();
		moveState = bat::MoveOff;
	}
}

