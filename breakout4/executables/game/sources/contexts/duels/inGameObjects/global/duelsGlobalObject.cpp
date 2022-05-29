#include "contexts/duels/inGameObjects/global/duelsGlobalObject.h"
#include "types/essentialsStruct.h"
#include "types/brickData.h"
#include "contexts/duels/instructions/elementsCollisions.h"
#include "contexts/duels/instructions/positionCheck.h"
#include "contexts/duels/instructions/activateBonuses.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

duels::GlobalObject::GlobalObject(Essentials& essentials, const sdl2::Font& arialFont, const std::vector< Offset >& spawnsCoord, const duels::LevelOptions& levelOptions):
	isLoadingPerfect{true},
	coins{essentials.logs, essentials.rndWnd, spawnsCoord, levelOptions},
	balls{essentials.logs, essentials.rndWnd, spawnsCoord, levelOptions},
	players{essentials.logs, essentials.prefPath, essentials.rndWnd, arialFont, levelOptions},
	randomGen{-SQR_SIZE, SQR_SIZE, 1},
	zoneSpecificFlags{false, false},
	commonSounds{essentials, duels::COMMON_SNDS_FILE_PATH, duels::COMMON_CHANNELS_FILE_PATH},
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
								const std::array< bool, duels::PLAYER_MAX>& canMoveRackToLeft, const std::array<bool, duels::PLAYER_MAX>& canMoveRackToRight,
								const std::array<bool, duels::PLAYER_MAX>& canActivateSpecialBonus)
{
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
	for( unsigned player{0} ; player < duels::PLAYER_MAX ; ++player )
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
	for( std::size_t i{0} ; i < duels::COIN_MAX ; ++i )
	{
		for( std::size_t j{0} ; j < duels::COIN_MAX ; ++j )
		{
			resetCoinToCoin(i, coins.coinsData[i], j, coins.coinsData[j], duels::COIN_RECT);
			coinToCoinBouncing(i, coins.coinsData[i], j, coins.coinsData[j], duels::COIN_RECT);
		}
	}
}

void duels::GlobalObject::testCoinToBallCollisions()
{
	for( std::size_t coinIndex{0} ; coinIndex < duels::COIN_MAX ; ++coinIndex )
	{
		for( std::size_t ballIndex{0} ; ballIndex < duels::BALL_MAX ; ++ballIndex )
		{
			resetCoinToBall(coinIndex, coins.coinsData[coinIndex], duels::COIN_RECT, ballIndex, balls.ballsData[ballIndex], duels::BALL_RECT);
			coinToBallBouncing(coinIndex, coins.coinsData[coinIndex], duels::COIN_RECT, ballIndex, balls.ballsData[ballIndex], duels::BALL_RECT);
		}
	}
}

void duels::GlobalObject::testBallToBallCollisions()
{
	for( std::size_t i{0} ; i < duels::BALL_MAX ; ++i )
	{
		for( std::size_t j{0} ; j < duels::BALL_MAX ; ++j )
		{
			resetBallToBall(i, balls.ballsData[i], j, balls.ballsData[j], duels::BALL_RECT);
			ballToBallBouncing(i, balls.ballsData[i], j, balls.ballsData[j], duels::BALL_RECT);
		}
	}
}

void duels::GlobalObject::testCoinToRacketsCollision()
{
	for( unsigned playerNum{0} ; playerNum < duels::PLAYER_MAX ; ++playerNum )
	{
		for( auto &coin : coins.coinsData )
		{
			if( doesMoveObjectCollideWithRect(coin.move, SpriteSize{COIN_TEXTURE_SIZE, COIN_TEXTURE_SIZE}, players.rackets[playerNum].getRacketRect() ) && coin.collision.isEffective )
			{
				commonSounds.playSound(duels::SND_COL_COIN_WRACKET);
				coin.collision.isEffective = false;
				players.bonusGenerator[playerNum].playerGetBonusCoin();
			}
		}
	}
}

void duels::GlobalObject::compareBallsPositionWithRacketsRects()
{
	for( unsigned playerNum{0} ; playerNum < duels::PLAYER_MAX ; ++playerNum )
	{
		for( auto &ball : balls.ballsData )
		{
			if( ball.collision.isEffective && ball.collision.checkWRacketsCollisions[playerNum] 
				&& doesMoveObjectCollideWithRect(ball.move, SpriteSize{BALL_TEXTURE_SIZE, BALL_TEXTURE_SIZE}, players.rackets[playerNum].getRacketRect()) )
			{
				makeBallsBounceAgainstRacket(ball.move, players.rackets[playerNum].getRacketRect());
				ball.collision.checkWRacketsCollisions[playerNum] = false;
			}
		}
	}
}

void duels::GlobalObject::makeBallsBounceAgainstRacket(ObjectMoving& ballMove, const SDL_Rect& racketRect)
{
	if( ballMove.get_x_position() + BALL_TEXTURE_SIZE / 2 < racketRect.x + duels::RACKET_SLOPE_INTERVAL )
	{
		commonSounds.playSound(duels::SND_COL_RACK_WBALL);
		giveObjectNewDirection(ballMove, Offset{-1, -1});
	}
	else if(   ballMove.get_x_position() + BALL_TEXTURE_SIZE / 2 >= racketRect.x + duels::RACKET_SLOPE_INTERVAL
			&& ballMove.get_x_position() - BALL_TEXTURE_SIZE / 2 < racketRect.x + racketRect.w - duels::RACKET_SLOPE_INTERVAL )
	{
		commonSounds.playSound(duels::SND_COL_RACK_WBALL);
		ballMove.reverse_y_vector();
		ballMove.adjust_y_speed();
	}
	else if( ballMove.get_x_position() - BALL_TEXTURE_SIZE / 2 > racketRect.x + racketRect.w - duels::RACKET_SLOPE_INTERVAL )
	{
		commonSounds.playSound(duels::SND_COL_RACK_WBALL);
		giveObjectNewDirection(ballMove, Offset{1, -1});
	}
}

void duels::GlobalObject::resetBallToRacketsCollisionStatus()
{
	for( unsigned playerNum{0} ; playerNum < duels::PLAYER_MAX ; ++playerNum )
	{
		for( auto &ball : balls.ballsData )
		{
			if( false == doesMoveObjectCollideWithRect(ball.move, SpriteSize{BALL_TEXTURE_SIZE, BALL_TEXTURE_SIZE}, enlargeGivenRect(players.rackets[playerNum].getRacketRect(), SQR_SIZE / 16 ) ) )
			{
				ball.collision.checkWRacketsCollisions[playerNum] = true;
			}
		}
	}
}

void duels::GlobalObject::moveRackets(const std::array< bool, duels::PLAYER_MAX>& canMoveRackToLeft, const std::array< bool, duels::PLAYER_MAX>& canMoveRackToRight)
{
	for( unsigned player{0} ; player < duels::PLAYER_MAX ; ++player )
	{
		players.moveRacket(player, canMoveRackToLeft[player], canMoveRackToRight[player]);
	}
}

void duels::GlobalObject::handleBonuses(duels::LevelOptions& levelOptions, const std::array<bool, duels::PLAYER_MAX>& canActivateSpecialBonus)
{
	for( unsigned playerNum{0} ; playerNum < duels::PLAYER_MAX ; ++playerNum )
	{
		if( players.bonusGenerator[playerNum].isAnyBonusReady() && players.playersInputs.getInputState(playerNum, duels::INP_ACTIVBONUS) )
		{
			actAccordingToBonus(playerNum, levelOptions, canActivateSpecialBonus[playerNum]);
			players.playersInputs.setInputState(playerNum, duels::INP_ACTIVBONUS);
		}
	}
}

void duels::GlobalObject::actAccordingToBonus(unsigned playerNum, duels::LevelOptions& levelOptions, bool canActivateSpecialBonus)
{
	switch( players.bonusGenerator[playerNum].getBonusType() )
	{
		case duels::DB_IMPROVE_SIZE_SELF:
			duels::improveSizeSelf(players.bonusGenerator[playerNum], players.rackets[playerNum], commonSounds);
			break;
		case duels::DB_SHRK_SIZE_OPPON:
			duels::shrinkOpponent(players.bonusGenerator[playerNum], players.rackets[getOpponent(playerNum)], commonSounds);
			break;
		case duels::DB_FREEZE_OPPON:
			duels::freezeOpponent(players.bonusGenerator[playerNum], players.rackets[getOpponent(playerNum)], commonSounds);
			break;
		case duels::DB_STEAL_BONUS_OPPON:
			duels::stealOpponentBonus(players.bonusGenerator[playerNum], players.bonusGenerator[getOpponent(playerNum)], commonSounds);
			break;
		case duels::DB_ACCEL_SELF:
			duels::accelerateSelf(players.bonusGenerator[playerNum], players.rackets[playerNum], players.racketsSpeedGradients[playerNum], commonSounds);
			break;
		case duels::DB_SLOWDOWN_OPPON:
			duels::slowDownOpponent(players.bonusGenerator[playerNum], players.rackets[getOpponent(playerNum)], players.racketsSpeedGradients[getOpponent(playerNum)], commonSounds);
			break;
		case duels::DB_ADD_BALL:
			duels::addBall(players.bonusGenerator[playerNum], balls, levelOptions);
			break;
		case duels::DB_ZONE_SPECIFIC:
			duels::activeZoneSpecificBonus(players.bonusGenerator[playerNum], zoneSpecificFlags[playerNum], canActivateSpecialBonus);
			break;
		case duels::DB_NEGATIVE_BONUS:
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