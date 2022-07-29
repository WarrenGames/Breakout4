#include "contexts/onePlayerGame/levelComponents/freeFunctions/detectLevelEnd.h"
#include "contexts/onePlayerGame/levelComponents/balls/ballsThings.h"
#include "crossLevel/playerData.h"
#include "generic/sounds/soundHandler.h"
#include "contexts/onePlayerGame/levelComponents/infoBar/infoBar.h"
#include "matrices/matrix2D.h"
#include "types/brickData.h"
#include "consts/constexprScreen.h"
#include "consts/onePlayerGridConsts.h"
#include "consts/onePlayerLevelConsts.h"

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
		case BRICKS::INDEX::GEN_BRICK:
			neededBricksNumber++;
			break;
		case BRICKS::INDEX::RICH_BRICK:
			neededBricksNumber++;
			break;
		case BRICKS::INDEX::BONUS_COIN:
			neededBricksNumber++;
			break;
		case BRICKS::INDEX::GIFT_BRICK:
			neededBricksNumber++;
			break;
		case BRICKS::INDEX::TEN_POINTS:
			tenPointsBricksNumber++;
			break;
	}
}

unsigned getLevelEnd(unsigned tenPointsBricksNumber, unsigned neededBricksNumber)
{
	if( neededBricksNumber == 0 )
	{
		if( tenPointsBricksNumber == 0 )
			return onePlGame::LEVEL_END_COMPLETE;
		else
			return onePlGame::LEVEL_END_PARTIALLY;
	}
	else{
		return onePlGame::LEVEL_END_NO;
	}
}

void detectLiveLossWithScreenBottom(BallThings& ball, unsigned& levelEndType, PlayerData& playerData, const SoundHandler& sounds, InfoBar& infoBar)
{
	if( ball.isMainBallActive && ball.move.get_y_position() > GAME_SCREEN_HEIGHT - ball.texture.sprite.height() / 2 && ball.move.get_y_norm() > 0 )
	{
		sounds.playSound(onePlGame::SND_BALL_LOST);
		ball.isMainBallActive = false;
		setLevelEndIfAny(levelEndType, playerData, infoBar);
	}
}

void setLevelEndIfAny(unsigned& levelEndType, PlayerData& playerData, InfoBar& infoBar)
{
	if( playerData.playerLives == 0 )
	{
		levelEndType = onePlGame::LEVEL_END_SURRENDER;
	}
	else{
		playerData.playerLives--;
		infoBar.setUpdateFlag(infoBarTexts::BALLS_IN_BAG);
	}
}