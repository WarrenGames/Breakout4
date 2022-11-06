#include "contexts/duels/inGameObjects/global/duelsGlobalObject.h"
#include "types/essentialsStruct.h"
#include "types/brickData.h"
#include "contexts/duels/instructions/elementsCollisions.h"
#include "contexts/duels/instructions/positionCheck.h"
#include "contexts/duels/instructions/activateBonuses.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include <cassert>

duels::GlobalObject::GlobalObject(Essentials& essentials, const sdl2::Font& arialFont, const std::vector< Offset >& spawnsCoord, const duels::LevelOptions& levelOptions):
	isLoadingPerfect{true},
	coins{essentials.logs, essentials.rndWnd, spawnsCoord, levelOptions},
	balls{essentials.logs, essentials.rndWnd, spawnsCoord, levelOptions},
	players{essentials.logs, essentials.prefPath, essentials.rndWnd, arialFont, levelOptions},
	randomGen{-SQR_SIZE, SQR_SIZE, 1},
	zoneSpecificFlags{ false, false },
	commonSounds{essentials, duels::CommonSoundsFilePath, duels::CommonChannelsFilePath},
	givenPoints{0}
{
	if( !( coins.wasLoadingPerfect() && balls.wasLoadingPerfect() && players.wasLoadingPerfect() && commonSounds.wasLoadingPerfect() ) )
		isLoadingPerfect = false;
}

bool duels::GlobalObject::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

void duels::GlobalObject::update(const MatrixTemp2D<BrickData>& levelGrid, duels::LevelOptions& levelOptions, bool& quitZone, 
								const std::vector< bool >& canMoveRackToLeft, const std::vector< bool >& canMoveRackToRight,
								const std::vector< bool >& canActivateSpecialBonus)
{
	assert( canMoveRackToLeft.size() == duels::PlayerMax );
	assert( canMoveRackToRight.size() == duels::PlayerMax );
	assert( canActivateSpecialBonus.size() == duels::PlayerMax );
	coins.update(levelGrid, balls, randomGen, commonSounds);
	balls.update(levelGrid, levelOptions, coins, randomGen, commonSounds, players.scoresDrawing, givenPoints);
	players.update(quitZone);
	testCollisionsBetweenCoinsAndBalls();
	testCoinToRacketsCollision();
	moveRackets(canMoveRackToLeft, canMoveRackToRight);
	compareBallsPositionWithRacketsRects();
	resetBallToRacketsCollisionStatus();
	handleBonuses(levelOptions, canActivateSpecialBonus);
	players.updateRacketsFreezeState();
	checkPointsToPlayInZoneAchievement(levelOptions, quitZone);
}

void duels::GlobalObject::drawEverything(sdl2::RendererWindow& rndWnd)
{
	players.drawRackets(rndWnd);
	players.drawBonusVignettes(rndWnd);
	players.drawSpeedGradientsBackground(rndWnd);
	players.drawSpeedGradients(rndWnd);
	players.drawPlayersScores(rndWnd);
	coins.drawBonusCoins(rndWnd);
	balls.drawBalls(rndWnd);
}

void duels::GlobalObject::resetScoresTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& arial, duels::LevelOptions& levelOptions)
{
	for( unsigned player{0} ; player < duels::PlayerMax ; ++player )
	{
		players.scoresDrawing[player].updateIfPossible(logs, rndWnd, arial, levelOptions.playersScores[player] );
	}
}

bool duels::GlobalObject::canConsumeZoneSpecificFlag(unsigned playerNum)
{
	if( zoneSpecificFlags[playerNum] )
	{
		zoneSpecificFlags[playerNum] = false;
		return true;
	}
	else
		return false;
}

void duels::GlobalObject::testCollisionsBetweenCoinsAndBalls()
{
	testCoinToCoinCollisions();
	testCoinToBallCollisions();
	testBallToBallCollisions();
}

void duels::GlobalObject::testCoinToCoinCollisions()
{
	for( std::size_t i{0} ; i < duels::CoinMaxNumber ; ++i )
	{
		for( std::size_t j{0} ; j < duels::CoinMaxNumber ; ++j )
		{
			resetCoinToCoin(i, coins.coinsData[i], j, coins.coinsData[j], duels::CoinRect);
			coinToCoinBouncing(i, coins.coinsData[i], j, coins.coinsData[j], duels::CoinRect);
		}
	}
}

void duels::GlobalObject::testCoinToBallCollisions()
{
	for( std::size_t coinIndex{0} ; coinIndex < duels::CoinMaxNumber ; ++coinIndex )
	{
		for( std::size_t ballIndex{0} ; ballIndex < duels::BallMaxNumber ; ++ballIndex )
		{
			resetCoinToBall(coinIndex, coins.coinsData[coinIndex], duels::CoinRect, ballIndex, balls.ballsData[ballIndex], duels::BallRect);
			coinToBallBouncing(coinIndex, coins.coinsData[coinIndex], duels::CoinRect, ballIndex, balls.ballsData[ballIndex], duels::BallRect);
		}
	}
}

void duels::GlobalObject::testBallToBallCollisions()
{
	for( std::size_t i{0} ; i < duels::BallMaxNumber ; ++i )
	{
		for( std::size_t j{0} ; j < duels::BallMaxNumber ; ++j )
		{
			resetBallToBall(i, balls.ballsData[i], j, balls.ballsData[j], duels::BallRect);
			ballToBallBouncing(i, balls.ballsData[i], j, balls.ballsData[j], duels::BallRect);
		}
	}
}

void duels::GlobalObject::testCoinToRacketsCollision()
{
	for( unsigned playerNum{0} ; playerNum < duels::PlayerMax ; ++playerNum )
	{
		for( auto &coin : coins.coinsData )
		{
			if( doesMoveObjectCollideWithRect(coin.move, SpriteSize{CoinTextureSize, CoinTextureSize}, players.rackets[playerNum].getRacketRect() ) && coin.collision.isEffective )
			{
				commonSounds.playSound(duels::SoundCollisionCoinWithRacket);
				coin.collision.isEffective = false;
				players.bonusGenerator[playerNum].playerGetBonusCoin();
			}
		}
	}
}

void duels::GlobalObject::compareBallsPositionWithRacketsRects()
{
	for( unsigned playerNum{0} ; playerNum < duels::PlayerMax ; ++playerNum )
	{
		for( auto &ball : balls.ballsData )
		{
			if( ball.collision.isEffective && ball.collision.checkWRacketsCollisions[playerNum] 
				&& doesMoveObjectCollideWithRect(ball.move, SpriteSize{BallTextureSize, BallTextureSize}, players.rackets[playerNum].getRacketRect()) )
			{
				makeBallsBounceAgainstRacket(ball.move, players.rackets[playerNum].getRacketRect());
				ball.collision.checkWRacketsCollisions[playerNum] = false;
			}
		}
	}
}

void duels::GlobalObject::makeBallsBounceAgainstRacket(spriteMove::ObjectMoving& ballMove, const SDL_Rect& racketRect)
{
	if( ballMove.get_x_position() + BallTextureSize / 2 < racketRect.x + duels::RacketSlopeInterval )
	{
		commonSounds.playSound(duels::SoundCollisionRacketWithBall);
		giveObjectNewDirection(ballMove, Offset{-1, -1});
	}
	else if(   ballMove.get_x_position() + BallTextureSize / 2 >= racketRect.x + duels::RacketSlopeInterval
			&& ballMove.get_x_position() - BallTextureSize / 2 < racketRect.x + racketRect.w - duels::RacketSlopeInterval )
	{
		commonSounds.playSound(duels::SoundCollisionRacketWithBall);
		ballMove.reverse_y_vector();
		ballMove.adjust_y_speed();
	}
	else if( ballMove.get_x_position() - BallTextureSize / 2 > racketRect.x + racketRect.w - duels::RacketSlopeInterval )
	{
		commonSounds.playSound(duels::SoundCollisionRacketWithBall);
		giveObjectNewDirection(ballMove, Offset{1, -1});
	}
}

void duels::GlobalObject::resetBallToRacketsCollisionStatus()
{
	for( unsigned playerNum{0} ; playerNum < duels::PlayerMax ; ++playerNum )
	{
		for( auto &ball : balls.ballsData )
		{
			if( false == doesMoveObjectCollideWithRect(ball.move, SpriteSize{BallTextureSize, BallTextureSize}, enlargeGivenRect(players.rackets[playerNum].getRacketRect(), SQR_SIZE / 16 ) ) )
			{
				ball.collision.checkWRacketsCollisions[playerNum] = true;
			}
		}
	}
}

void duels::GlobalObject::moveRackets(const std::vector< bool >& canMoveRackToLeft, const std::vector< bool >& canMoveRackToRight)
{
	for( unsigned player{0} ; player < duels::PlayerMax ; ++player )
	{
		players.moveRacket(player, canMoveRackToLeft[player], canMoveRackToRight[player]);
	}
}

void duels::GlobalObject::handleBonuses(duels::LevelOptions& levelOptions, const std::vector< bool >& canActivateSpecialBonus)
{
	for( unsigned playerNum{0} ; playerNum < duels::PlayerMax ; ++playerNum )
	{
		if( players.bonusGenerator[playerNum].isAnyBonusReady() && players.playersInputs.getInputState(playerNum, duels::InputActiveBonus) )
		{
			actAccordingToBonus(playerNum, levelOptions, canActivateSpecialBonus[playerNum]);
			players.playersInputs.setInputState(playerNum, duels::InputActiveBonus);
		}
	}
}

void duels::GlobalObject::actAccordingToBonus(unsigned playerNum, duels::LevelOptions& levelOptions, bool canActivateSpecialBonus)
{
	switch( players.bonusGenerator[playerNum].getBonusType() )
	{
		case duels::BonusImproveSizeSelf:
			duels::improveSizeSelf(players.bonusGenerator[playerNum], players.rackets[playerNum], commonSounds);
			break;
		case duels::BonusShrinkOpponentSize:
			duels::shrinkOpponent(players.bonusGenerator[playerNum], players.rackets[getOpponent(playerNum)], commonSounds);
			break;
		case duels::BonusFreezeOpponent:
			duels::freezeOpponent(players.bonusGenerator[playerNum], players.rackets[getOpponent(playerNum)], commonSounds);
			break;
		case duels::BonusStealOpponentBonus:
			duels::stealOpponentBonus(players.bonusGenerator[playerNum], players.bonusGenerator[getOpponent(playerNum)], commonSounds);
			break;
		case duels::BonusSpeedUpSelf:
			duels::accelerateSelf(players.bonusGenerator[playerNum], players.rackets[playerNum], players.racketsSpeedGradients[playerNum], commonSounds);
			break;
		case duels::BonusSlowDownOpponent:
			duels::slowDownOpponent(players.bonusGenerator[playerNum], players.rackets[getOpponent(playerNum)], players.racketsSpeedGradients[getOpponent(playerNum)], commonSounds);
			break;
		case duels::BonusAddBall:
			duels::addBall(players.bonusGenerator[playerNum], balls, levelOptions);
			break;
		case duels::BonusZoneSpecific:
			duels::activeZoneSpecificBonus(players.bonusGenerator[playerNum], zoneSpecificFlags[playerNum], canActivateSpecialBonus);
			break;
		case duels::BonusNegativeBonus:
			duels::negativeBonus(players.bonusGenerator[playerNum], levelOptions.playersScores[playerNum], commonSounds, players.scoresDrawing[playerNum]);
			break;
		default:
			
			break;
	}
}

void duels::GlobalObject::checkPointsToPlayInZoneAchievement(duels::LevelOptions& levelOptions, bool& quitZone)
{
	if( givenPoints >= levelOptions.pointsToPlayInZone )
	{
		quitZone = true;
	}
}