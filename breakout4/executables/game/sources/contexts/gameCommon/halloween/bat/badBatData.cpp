#include "contexts/gameCommon/halloween/bat/badBatData.h"
#include "consts/constexprScreen.h"
#include <cassert>

BadBatData::BadBatData():
	wingsFrameNumber{0},
	batMove{AccurCoords{-SQR_SIZE*5, GAME_SCREEN_HEIGHT + SQR_SIZE *4}, 0, Offset{1, 0}},
	wingsAnim{},
	batMoveDelay{},
	wingsMoveDown{true},
	faceIndex{bat::FACE_EFFORT},
	moveState{bat::MOVE_OFF},
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
	assert( newMoveState <= bat::MOVE_FROM_LEFT );
	moveState = newMoveState;
	batMove.setBothVectors(newVectors);
	batMove.adjust_x_speed();
	batMove.adjust_y_speed();
}

void BadBatData::changeFace(std::size_t newFace)
{
	assert( newFace < bat::FACE_MAX );
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
	moveState = bat::MOVE_FROM_LEFT;
	batMove.setPosition(Offset{-SQR_SIZE*4, GAME_SCREEN_HEIGHT - SQR_SIZE*4});
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
			if( wingsFrameNumber < bat::WING_IMG_NUMBER - 1 )
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
	if( batMoveDelay.hasTimeElapsed( std::chrono::milliseconds{10} ) && (moveState == bat::MOVE_FROM_LEFT || moveState == bat::MOVE_FROM_RIGHT) )
	{
		batMove.moveObject();
		batMoveDelay.joinTimePoints();
	}
}

void BadBatData::stopBat()
{
	if( 	(moveState == bat::MOVE_FROM_LEFT && batMove.getPosition().x >= GAME_SCREEN_WIDTH + SQR_SIZE *3 )
		||	(moveState == bat::MOVE_FROM_RIGHT && batMove.getPosition().x <= -SQR_SIZE * 3 ) )
	{
		batMove.setSpeed(0);
		batMove.adjust_x_speed();
		batMove.adjust_y_speed();
		moveState = bat::MOVE_OFF;
	}
}

