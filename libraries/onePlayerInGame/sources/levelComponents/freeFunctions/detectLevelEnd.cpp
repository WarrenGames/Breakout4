#include "levelComponents/freeFunctions/detectLevelEnd.h"
#include "levelComponents/balls/ballsThings.h"
#include "crossLevel/playerData.h"
#include "soundSystem/soundsPlayer.h"
#include "levelComponents/infoBar/infoBar.h"
#include "levelComponents/infoBar/playedTimeCounter.h"
#include "matrices/matrix2D.h"
#include "types/brickData.h"
#include "consts/constexprScreen.h"
#include "consts/onePlayerGridConsts.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/onePlayerSounds.h"

void countBricks(const MatrixTemp2D<BrickData>& levelMat, unsigned& levelEndType)
{
	unsigned tenPointsBricksNumber{0};
	unsigned neededBricksNumber{0};
	for( std::size_t width{0} ; width < levelMat.width() ; ++width )
	{
		for( std::size_t height{0} ; height < levelMat.height() ; ++height )
		{
			incrementAccordingToBrickID(levelMat(width, height), neededBricksNumber, tenPointsBricksNumber);
		}
	}
	levelEndType = getLevelEnd(tenPointsBricksNumber, neededBricksNumber);
}

void incrementAccordingToBrickID(const BrickData& brickData, unsigned& neededBricksNumber, unsigned& tenPointsBricksNumber)
{
	switch( brickData.index )
	{
		case bricks::index::GenericBrick:
			neededBricksNumber++;
			break;
		case bricks::index::RichBrick:
			neededBricksNumber++;
			break;
		case bricks::index::BonusCoin:
			neededBricksNumber++;
			break;
		case bricks::index::GiftBrick:
			neededBricksNumber++;
			break;
		case bricks::index::TenPointsBrick:
			tenPointsBricksNumber++;
			break;
	}
}

unsigned getLevelEnd(unsigned tenPointsBricksNumber, unsigned neededBricksNumber)
{
	if( neededBricksNumber == 0 )
	{
		if( tenPointsBricksNumber == 0 )
			return onePlGame::LevelEndComplete;
		else
			return onePlGame::LevelEndPartially;
	}
	else{
		return onePlGame::LevelEndNotYet;
	}
}

void detectLiveLossWithScreenBottom(BallThings& ball, unsigned& levelEndType, PlayerData& playerData, const SoundPlayer& soundPlayer, InfoBar& infoBar, PlayedTimeCounter& playedTimeCounter)
{
	if( ball.isMainBallActive && ball.move.get_y_position() > GameScreenHeight - ball.texture.sprite.height() / 2 && ball.move.get_y_norm() > 0 )
	{
		soundPlayer.playSoundOnGroup(onePlGame::SoundBallLost, onePlGame::GroupTagRacketWithBallCollision);
		ball.isMainBallActive = false;
		setLevelEndIfAny(levelEndType, playerData, infoBar);
		playedTimeCounter.pauseTheGame();
	}
}

void setLevelEndIfAny(unsigned& levelEndType, PlayerData& playerData, InfoBar& infoBar)
{
	if( playerData.playerLives == 0 )
	{
		levelEndType = onePlGame::LevelEndSurrender;
	}
	else{
		playerData.playerLives--;
		infoBar.setUpdateFlag(infoBarTexts::BallsInBag);
	}
}