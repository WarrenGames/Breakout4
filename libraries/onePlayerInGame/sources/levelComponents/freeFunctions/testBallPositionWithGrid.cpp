#include "levelComponents/freeFunctions/testBallPositionWithGrid.h"
#include "levelComponents/global/globalGameObject.h"
#include "crossLevel/playerData.h"
#include "levelComponents/freeFunctions/detectLevelEnd.h"
#include "levelComponents/freeFunctions/ballWithGridCollisions.h"
#include "consts/gridOffsetCoord.h"
#include "consts/onePlayerSounds.h"

bool ballCol::isThereAnElementInGrid(LevelComponents& comp, const Offset& coords)
{
	if( comp.grid.isSignedInsideBoundaries(coords.x, coords.y) )
	{
		return comp.grid(coords.x, coords.y).index != bricks::index::NoBrick;
	}
	else
		return false;
}

void ballCol::testLeftCollision(LevelComponents& comp, BallThings& ball, PlayerData& playerData)
{
	if( ball.move.get_x_norm() < 0 
		&& ball.move.get_x_position() % SQR_SIZE < ball.texture.sprite.width() / 2
		&& ballCol::isThereAnElementInGrid(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::Left) ) )
	{
		gridCol::collideBallWithBricksMatrix(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::Left), ball, playerData );
		ball.move.reverse_x_vector();
		ball.move.adjust_x_speed();
		countBricks(comp.grid, comp.levelEndType);
		comp.infoBar.setUpdateFlag(infoBarTexts::PlayerScore);
		comp.infoBar.setUpdateFlag(infoBarTexts::BonusCoinNumber);
	}
}

void ballCol::testRightCollision(LevelComponents& comp, BallThings& ball, PlayerData& playerData)
{
	if( ball.move.get_x_norm() > 0 
		&& ball.move.get_x_position() % SQR_SIZE > SQR_SIZE - ball.texture.sprite.width() / 2 
		&& ballCol::isThereAnElementInGrid(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::Right) ) )
	{
		gridCol::collideBallWithBricksMatrix(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::Right), ball, playerData  );
		ball.move.reverse_x_vector();
		ball.move.adjust_x_speed();
		countBricks(comp.grid, comp.levelEndType);
		comp.infoBar.setUpdateFlag(infoBarTexts::PlayerScore);
		comp.infoBar.setUpdateFlag(infoBarTexts::BonusCoinNumber);
	}
}

void ballCol::testTopCollision(LevelComponents& comp, BallThings& ball, PlayerData& playerData)
{
	if( ball.move.get_y_norm() < 0 
		&& ball.move.get_y_position() % SQR_SIZE < ball.texture.sprite.height() / 2 
		&& ballCol::isThereAnElementInGrid(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::Top) ) )
	{
		gridCol::collideBallWithBricksMatrix(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::Top), ball, playerData  );
		ball.move.reverse_y_vector();
		ball.move.adjust_y_speed();
		countBricks(comp.grid, comp.levelEndType);
		comp.infoBar.setUpdateFlag(infoBarTexts::PlayerScore);
		comp.infoBar.setUpdateFlag(infoBarTexts::BonusCoinNumber);
	}
}

void ballCol::testBottomCollision(LevelComponents& comp, BallThings& ball, PlayerData& playerData)
{
	if( ball.move.get_y_norm() > 0 
		&& ball.move.get_y_position() % SQR_SIZE > SQR_SIZE - ball.texture.sprite.height() / 2 
		&& ballCol::isThereAnElementInGrid(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::Bottom) ) )
	{
		gridCol::collideBallWithBricksMatrix(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::Bottom), ball, playerData  );
		ball.move.reverse_y_vector();
		ball.move.adjust_y_speed();
		countBricks(comp.grid, comp.levelEndType);
		comp.infoBar.setUpdateFlag(infoBarTexts::PlayerScore);
		comp.infoBar.setUpdateFlag(infoBarTexts::BonusCoinNumber);
	}
}

void ballCol::testTopLeftCollision(LevelComponents& comp, BallThings& ball, PlayerData& playerData)
{
	if( ball.move.get_x_norm() < 0
		&& ball.move.get_y_norm() < 0
		&& ball.move.get_x_position() % SQR_SIZE < ball.texture.sprite.width() / 2 - onePlGame::BallCornerInterval 
		&& ball.move.get_y_position() % SQR_SIZE < ball.texture.sprite.height() / 2 - onePlGame::BallCornerInterval 
		&& isThereAnElementInGrid(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::TopLeft) ) 
		&& false == ballCol::isThereAnElementInGrid(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::Top) )
		&& false == ballCol::isThereAnElementInGrid(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::Left) ) )
	{
		ballCol::appendCornerBallModifications(comp, playerData, position::BottomRight, position::TopLeft);
	}
}

void ballCol::testTopRightCollision(LevelComponents& comp, BallThings& ball, PlayerData& playerData)
{
	if( ball.move.get_x_norm() > 0 
		&& ball.move.get_y_norm() < 0 
		&& ball.move.get_x_position() % SQR_SIZE > SQR_SIZE - ball.texture.sprite.width() / 2 + onePlGame::BallCornerInterval 
		&& ball.move.get_y_position() % SQR_SIZE < ball.texture.sprite.height() / 2  - onePlGame::BallCornerInterval 
		&& ballCol::isThereAnElementInGrid(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::TopRight) ) 
		&& false == ballCol::isThereAnElementInGrid(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::Top) ) 
		&& false == ballCol::isThereAnElementInGrid(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::Right) ) )
	{
		ballCol::appendCornerBallModifications(comp, playerData, position::BottomLeft, position::TopRight);
	}
}

void ballCol::testBottomLeftCollision(LevelComponents& comp, BallThings& ball, PlayerData& playerData)
{
	if( ball.move.get_x_norm() < 0 
		&& ball.move.get_y_norm() > 0
		&& ball.move.get_x_position() % SQR_SIZE < ball.texture.sprite.width() / 2 - onePlGame::BallCornerInterval 
		&& ball.move.get_y_position() % SQR_SIZE > SQR_SIZE - ball.texture.sprite.height() / 2 + onePlGame::BallCornerInterval 
		&& ballCol::isThereAnElementInGrid(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::BottomLeft) )
		&& false == ballCol::isThereAnElementInGrid(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::Bottom) ) 
		&& false == ballCol::isThereAnElementInGrid(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::Left) ) )
	{
		ballCol::appendCornerBallModifications(comp, playerData, position::TopRight, position::BottomLeft);
	}
}

void ballCol::testBottomRightCollision(LevelComponents& comp, BallThings& ball, PlayerData& playerData)
{
	if( ball.move.get_x_norm() > 0 && ball.move.get_y_norm() > 0 
		&& ball.move.get_x_position() % SQR_SIZE > SQR_SIZE - ball.texture.sprite.width() / 2 + onePlGame::BallCornerInterval 
		&& ball.move.get_y_position() % SQR_SIZE > SQR_SIZE - ball.texture.sprite.height() / 2 + onePlGame::BallCornerInterval 
		&& ballCol::isThereAnElementInGrid(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::BottomRight) ) 
		&& false == ballCol::isThereAnElementInGrid(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::Bottom) ) 
		&& false == ballCol::isThereAnElementInGrid(comp, ballCol::getBrickCoordinates(ball.gridRelPos, position::Right) ) )
	{
		ballCol::appendCornerBallModifications(comp, playerData, position::TopLeft, position::BottomRight);
	}
}

void ballCol::testScreenLeftCollision(LevelComponents& comp, BallThings& ball)
{
	if( ball.move.get_x_position() < ball.texture.sprite.width() / 2 
		&& ball.move.get_x_norm() < 0 )
	{
		comp.gameSoundSystem.soundSystem.soundPlayer.playSoundOnGroup(onePlGame::SoundBallWBgCollision, onePlGame::GroupTagRacketWithBallCollision);
		ball.move.reverse_x_vector();
		ball.move.adjust_x_speed();
	}
}

void ballCol::testScreenRightCollision(LevelComponents& comp, BallThings& ball)
{
	if( ball.move.get_x_position() > GameScreenWidth - ball.texture.sprite.width() / 2 
		&& ball.move.get_x_norm() > 0 )
	{
		comp.gameSoundSystem.soundSystem.soundPlayer.playSoundOnGroup(onePlGame::SoundBallWBgCollision, onePlGame::GroupTagRacketWithBallCollision);
		ball.move.reverse_x_vector();
		ball.move.adjust_x_speed();
	}
}

void ballCol::testScreenTopCollision(LevelComponents& comp, BallThings& ball)
{
	if( ball.move.get_y_position() < onePlGame::InfoBoardY_Margin * SQR_SIZE + ball.texture.sprite.height() / 2 
		&& ball.move.get_y_norm() < 0 )
	{
		comp.gameSoundSystem.soundSystem.soundPlayer.playSoundOnGroup(onePlGame::SoundBallWBgCollision, onePlGame::GroupTagRacketWithBallCollision);
		ball.move.reverse_y_vector();
		ball.move.adjust_y_speed();
	}
}

void ballCol::testScreenBottomtCollision(LevelComponents& comp, BallThings& ball)
{
	if( ball.move.get_y_position() > GameScreenHeight - ball.texture.sprite.height() / 2 
		&& ball.move.get_y_norm() > 0 )
	{
		comp.gameSoundSystem.soundSystem.soundPlayer.playSoundOnGroup(onePlGame::SoundBallWBgCollision, onePlGame::GroupTagRacketWithBallCollision);
		ball.move.reverse_y_vector();
		ball.move.adjust_y_speed();
	}
}


Offset ballCol::getBrickCoordinates(const Offset& ballToGridPosition, const Offset& ballRelativeBrickPos)
{
	return Offset{ ballToGridPosition.x + ballRelativeBrickPos.x, ballToGridPosition.y + ballRelativeBrickPos.y };
}

void ballCol::appendCornerBallModifications(LevelComponents& comp, PlayerData& playerData, const Offset& newBallDir, const Offset& brickCoord)
{
	gridCol::collideBallWithBricksMatrix(comp, ballCol::getBrickCoordinates(comp.ball.gridRelPos, brickCoord), comp.ball, playerData);
	giveObjectNewDirection(comp.ball.move, newBallDir);
	countBricks(comp.grid, comp.levelEndType);
	comp.infoBar.setUpdateFlag(infoBarTexts::PlayerScore);
	comp.infoBar.setUpdateFlag(infoBarTexts::BonusCoinNumber);
}