#include "contexts/duels/inGameObjects/balls/ballsMain.h"
#include "contexts/duels/instructions/positionCheck.h"
#include "contexts/gameCommon/rectCollisions/brickGridCollisions.h"
#include "contexts/duels/instructions/objMoveWRectCollide.h"
#include "contexts/duels/instructions/elementsCollisions.h"
#include "contexts/duels/inGameObjects/bonusCoins/coinsMain.h"
#include "contexts/duels/inGameObjects/playerScore/playerScoreDrawing.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "generic/sounds/soundHandler.h"
#include "matrices/matrix2D.h"
#include "types/brickData.h"
#include "random/randomGenerator.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include <algorithm>
#include <cassert>

duels::BallsThings::BallsThings(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::vector< Offset >& spawnsCoord, const duels::LevelOptions& levelOptions):
	ballsData(duels::BallMaxNumber),
	ballTexture{logs, rndWnd, "textures/sprites/balls/yellowBall.png"},
	ballsMove{},
	ballsSpeedIncr{},
	collisionBools{},
	canCheckForScores{true},
	spawns{levelOptions.secondsBeforeNewBall, levelOptions.ballsMax, spawnsCoord}
{
	
}

bool duels::BallsThings::wasLoadingPerfect() const
{
	return ballTexture.texture;
}

void duels::BallsThings::update(const MatrixTemp2D<BrickData>& levelGrid, duels::LevelOptions& levelOptions, CoinsThings& coins, IntRandomGenerator& randomGen, const SoundHandler& commonSounds, 
								std::vector< duels::ScoreDraw >& scoreDrawing, unsigned& givenPoints)
{
	moveBalls();
	accelarateBallsSpeed();
	checkCollisionWithGrid(levelGrid, commonSounds);
	setCanCreateBall();
	testBallAndScreenRimsCollision();
	disableCoinIfOutsideScreen();
	createNewBallIfPossible(coins, randomGen);
	checkBallsPositionsForScore(levelOptions.playersScores, scoreDrawing, givenPoints);
}

void duels::BallsThings::moveBalls()
{
	if( ballsMove.hasTimeElapsed( std::chrono::milliseconds{10} ) )
	{
		for( auto &ball : ballsData )
		{
			if( ball.collision.isEffective )
			{
				ball.move.moveObject();
			}
		}
		canCheckForScores = true;
		collisionBools.resetAllCollisions();
		ballsMove.joinTimePoints();
	}
}

void duels::BallsThings::accelarateBallsSpeed()
{
	if( ballsSpeedIncr.hasTimeElapsed( std::chrono::milliseconds{4000} ) )
	{
		for( auto &ball : ballsData )
		{
			if( ball.collision.isEffective )
			{
				ball.move.incrementSpeed(0.1);
				ball.move.adjust_x_speed();
				ball.move.adjust_y_speed();
			}
		}
		ballsSpeedIncr.joinTimePoints();
	}
}

void duels::BallsThings::testBallAndScreenRimsCollision()
{
	if( collisionBools.canCheckCollisionWithScreenRim )
	{
		for( auto &ball : ballsData )
		{
			ball.bounceAgainstLeftOfScreen(ballTexture.sprite.width());
			ball.bounceAgainstRightOfScreen(ballTexture.sprite.width());
		}
		collisionBools.canCheckCollisionWithScreenRim = false;
	}
}

void duels::BallsThings::checkBallsPositionsForScore(std::vector< int >& playersScores, std::vector< duels::ScoreDraw >& scoreDrawing, unsigned& givenPoints)
{
	if( canCheckForScores )
	{
		giveBluePlayerAPoint(playersScores[duels::PlayerBlue], scoreDrawing[duels::PlayerBlue], givenPoints);
		giveRedPlayerAPoint(playersScores[duels::PlayerRed], scoreDrawing[duels::PlayerRed], givenPoints);
		canCheckForScores = false;
	}
}

void duels::BallsThings::giveBluePlayerAPoint(int& bluePlayerScore, duels::ScoreDraw& blueScore, unsigned& givenPoints)
{
	for( auto &ball : ballsData )
	{
		if( ball.collision.isEffective )
		{
			if( ball.move.get_y_position() < -SQR_SIZE / 2 )
			{
				bluePlayerScore++;
				ball.collision.isEffective = false;
				blueScore.setUpdateFlag();
				givenPoints++;
			}
		}
	}
}

void duels::BallsThings::giveRedPlayerAPoint(int& redPlayerScore, duels::ScoreDraw& redScore, unsigned& givenPoints)
{
	for( auto &ball : ballsData )
	{
		if( ball.collision.isEffective )
		{
			if( ball.move.get_y_position() > GameScreenHeight + SQR_SIZE / 2)
			{
				redPlayerScore++;
				ball.collision.isEffective = false;
				redScore.setUpdateFlag();
				givenPoints++;
			}
		}
	}
}

void duels::BallsThings::disableCoinIfOutsideScreen()
{
	for( auto &ball : ballsData )
	{
		if( ball.collision.isEffective )
		{
			if( ball.move.get_x_position() < -SQR_SIZE || ball.move.get_x_position() > GameScreenWidth + SQR_SIZE )
			{
				ball.collision.isEffective = false;
			}
		}
	}
}

void duels::BallsThings::checkCollisionWithGrid(const MatrixTemp2D<BrickData>& levelGrid, const SoundHandler& commonSounds)
{
	if( collisionBools.canCheckCollisionWithGrid )
	{
		for( auto &ball : ballsData )
		{
			if( ball.collision.isEffective)
			{
				bool wasThereCol{false};
				testGridCollisions(levelGrid, ball.move, SpriteSize{BallTextureSize, BallTextureSize}, wasThereCol);
				playSoundIfCollision(commonSounds, wasThereCol);
			}
		}
		collisionBools.canCheckCollisionWithGrid = false;
	}
}

unsigned duels::BallsThings::getEffectiveBallsCount() const
{
	return static_cast<unsigned>( std::count_if(ballsData.cbegin(), ballsData.cend(), [](auto ball){return ball.collision.isEffective;} ) );
}

std::size_t duels::BallsThings::getFirstFreeBallIndex() const
{
	for( std::size_t i{0} ; i < ballsData.size() ; ++i )
	{
		if( false == ballsData[i].collision.isEffective )
			return i;
	}
	return ballsData.size();
}

bool duels::BallsThings::isAnyBallOverSpawnPoint(const Offset& spawnPoint) const
{
	return std::any_of(ballsData.cbegin(), ballsData.cend(), [spawnPoint](auto ball){return isMoveObjectOverSpawnPoint(ball.move, SpriteSize{SQR_SIZE, SQR_SIZE}, spawnPoint);} );
}

void duels::BallsThings::createNewBallIfPossible(CoinsThings& coins, IntRandomGenerator& randomGen)
{
	if( spawns.canSpawnElement )
	{
		for( auto const &spawnPoint : spawns.spawnsCoordinates )
		{
			if( false == coins.isAnyCoinOverSpawnPoint(spawnPoint) && false == isAnyBallOverSpawnPoint(spawnPoint) && getEffectiveBallsCount() < spawns.maxElementNumber && spawns.canSpawnElement)
			{
				std::size_t index{ getFirstFreeBallIndex() };
				ballsData[index].makeBallEffective(spawnPoint, {randomGen.getRandomValue(), randomGen.getRandomValue()});
				if( ballsData[index].move.get_y_norm() == 0 )
				{
					ballsData[index].move.set_y_vector(-SQR_SIZE / 4);
				}
				spawns.canSpawnElement = false;
			}
		}
	}
}

void duels::BallsThings::setCanCreateBall()
{
	if( spawns.newElementDelay.hasTimeElapsed( std::chrono::milliseconds{spawns.secondsBeforeNewElement * 1000} ) )
	{
		spawns.canSpawnElement = true;
		spawns.newElementDelay.joinTimePoints();
	}
}

void duels::BallsThings::drawBalls(sdl2::RendererWindow& rndWnd)
{
	for( auto const &ball : ballsData )
	{
		if( ball.collision.isEffective )
		{
			ballTexture.drawToCenter(rndWnd, ball.move.get_x_position(), ball.move.get_y_position() );
		}
	}
}

void duels::BallsThings::checkCollisionWithRect(const SDL_Rect& externObjectRect, std::vector< bool >& canCollide)
{
	for( std::size_t ballNum{0} ; ballNum < duels::BallMaxNumber ; ++ballNum )
	{
		assert( ballNum < canCollide.size() );
		if( canCollide[ballNum] && doesMoveObjectCollideWithRect(ballsData[ballNum].move, SpriteSize{ballTexture.sprite.width(), ballTexture.sprite.height()}, externObjectRect) )
		{
			collision::makeObjectMoveBounceWithRect(ballsData[ballNum].move, SpriteSize{ballTexture.sprite.width(), ballTexture.sprite.height()}, externObjectRect);
			canCollide[ballNum] = false;
		}
		if( false == canCollide[ballNum] && 
			false == doesMoveObjectCollideWithRect(ballsData[ballNum].move, SpriteSize{ballTexture.sprite.width(), ballTexture.sprite.height()}, enlargeGivenRect(externObjectRect, SQR_SIZE / 8) ) )
		{
			canCollide[ballNum] = true;	
		}
	}
}

void duels::BallsThings::playSoundIfCollision(const SoundHandler& sounds, bool wasThereCol)
{
	if( wasThereCol )
	{
		sounds.playSound(duels::SoundCollisionBallWithBackground);
	}
}