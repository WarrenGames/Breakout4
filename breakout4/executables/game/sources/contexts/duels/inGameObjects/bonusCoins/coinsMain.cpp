#include "contexts/duels/inGameObjects/bonusCoins/coinsMain.h"
#include "contexts/duels/instructions/positionCheck.h"
#include "contexts/gameCommon/rectCollisions/brickGridCollisions.h"
#include "contexts/duels/instructions/objMoveWRectCollide.h"
#include "contexts/duels/inGameObjects/balls/ballsMain.h"
#include "contexts/duels/instructions/elementsCollisions.h"
#include "texturing/rendererWindow.h"
#include "matrices/matrix2D.h"
#include "generic/sounds/soundHandler.h"
#include "consts/constexprScreen.h"
#include "contexts/duels/duelsConstexpr.h"
#include "consts/sdlColors.h"
#include <algorithm>
#include <cassert>

constexpr SpriteSize COIN_RECT = { duels::COIN_TEXTURE_SIZE, duels::COIN_TEXTURE_SIZE };

duels::CoinsThings::CoinsThings(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::vector< Offset >& spawnsCoord, const duels::LevelOptions& levelOptions):
	coinsData( duels::COIN_MAX ),
	coinTextures{logs, rndWnd, "data/textures/coinTexturesList.txt"},
	coinSprites{coinTextures},
	coinsAnimation{},
	coinsMove{},
	collisionBools{},
	spawns{levelOptions.secondsBeforeNewCoin, levelOptions.coinsMax, spawnsCoord}
{
	
}

bool duels::CoinsThings::wasLoadingPerfect() const
{
	return coinTextures.wasLoadingPerfect();
}

void duels::CoinsThings::update(const MatrixTemp2D<BrickData>& levelGrid, BallsThings& balls, IntRandomGenerator& randomGen, const SoundHandler& commonSounds)
{
	animateCoins();
	moveCoins();
	testCoinAndScreenRimsCollision();
	disableCoinIfOutsideOfScreen();
	checkCollisionWithGrid(levelGrid);
	setCanCreateCoin();
	createNewCoinIfPossible(balls, randomGen, commonSounds);
}

void duels::CoinsThings::animateCoins()
{
	if( coinsAnimation.hasTimeElapsed( std::chrono::milliseconds{50} ) )
	{
		for( auto &coin : coinsData )
		{
			if( coin.collision.isEffective )
				coin.animateCoin();
		}
		coinsAnimation.joinTimePoints();
	}
}

void duels::CoinsThings::moveCoins()
{
	if( coinsMove.hasTimeElapsed( std::chrono::milliseconds{10} ) )
	{
		for( auto &coin : coinsData )
		{
			if( coin.collision.isEffective )
				coin.moveCoin();
		}
		collisionBools.resetAllCollisions();
		coinsMove.joinTimePoints();
	}
}

void duels::CoinsThings::testCoinAndScreenRimsCollision()
{
	for( auto &coin : coinsData )
	{
		if( coin.collision.isEffective )
		{
			coin.bounceAgainstLeftOfScreen();
			coin.bounceAgainstRightOfScreen();
		}
	}
}

void duels::CoinsThings::disableCoinIfOutsideOfScreen()
{
	for( auto &coin : coinsData )
	{
		if( false == isElementInsideOfScreen(coin.move, SpriteSize{SQR_SIZE, SQR_SIZE} ) )
		{
			coin.collision.isEffective = false;
		}
	}
}

void duels::CoinsThings::checkCollisionWithGrid(const MatrixTemp2D<BrickData>& levelGrid)
{
	if( collisionBools.canCheckCollisionWithGrid )
	{
		for( auto &coin : coinsData )
		{
			if( coin.collision.isEffective )
			{
				bool wasThereCollision{false};
				testGridCollisions(levelGrid, coin.move, SpriteSize{COIN_TEXTURE_SIZE, COIN_TEXTURE_SIZE}, wasThereCollision);
			}
		}
		collisionBools.canCheckCollisionWithGrid = false;
	}
}

unsigned duels::CoinsThings::getEffectiveCoinCount() const
{
	return static_cast<unsigned>( std::count_if(coinsData.cbegin(), coinsData.cend(), [](auto coin){return coin.collision.isEffective;} ) );
}

std::size_t duels::CoinsThings::getFirstFreeCoinIndex() const
{
	for( std::size_t i{0} ; i < coinsData.size() ; ++i )
	{
		if( false == coinsData[i].collision.isEffective )
			return i;
	}
	return coinsData.size();
}

bool duels::CoinsThings::isAnyCoinOverSpawnPoint(const Offset& spawnPoint) const
{
	return std::any_of(coinsData.cbegin(), coinsData.cend(), 
		[spawnPoint](auto coin){return isMoveObjectOverSpawnPoint(coin.move, SpriteSize{SQR_SIZE * 3 / 2, SQR_SIZE * 3 / 2}, spawnPoint); } );
}

void duels::CoinsThings::createNewCoinIfPossible(duels::BallsThings& balls, IntRandomGenerator& randomGen, const SoundHandler& commonSounds)
{
	if( spawns.canSpawnElement )
	{
		for( auto const &spawnPoint : spawns.spawnsCoordinates )
		{
			if( false == balls.isAnyBallOverSpawnPoint(spawnPoint) && false == isAnyCoinOverSpawnPoint(spawnPoint) && getEffectiveCoinCount() < spawns.maxElementNumber && spawns.canSpawnElement )
			{
				commonSounds.playSound(duels::SND_NEW_COIN);
				std::size_t index{ getFirstFreeCoinIndex() }; 
				coinsData[index].makeCoinEffective(spawnPoint, {randomGen.getRandomValue(), randomGen.getRandomValue()});
				if( coinsData[index].move.get_y_norm() == 0 )
				{
					coinsData[index].move.set_y_vector(SQR_SIZE / 4);
				}
				spawns.canSpawnElement = false;
			}
		}
	}
}

void duels::CoinsThings::setCanCreateCoin()
{
	if( spawns.newElementDelay.hasTimeElapsed( std::chrono::milliseconds{spawns.secondsBeforeNewElement * 1000} ) )
	{
		spawns.canSpawnElement = true;
		spawns.newElementDelay.joinTimePoints();
	}
}

void duels::CoinsThings::drawBonusCoins(sdl2::RendererWindow& rndWnd)
{
	for( auto const &coin : coinsData )
	{
		if( coin.collision.isEffective )
		{
			assert( coin.animIndex < coinSprites.size() );
			coinSprites.drawToCenter(rndWnd, coin.move.get_x_position(), coin.move.get_y_position(), coin.animIndex);
		}
	}
}

void duels::CoinsThings::checkCollisionWithRect(const SDL_Rect& externObjectRect, std::vector< bool >& canCollide)
{
	for( std::size_t coinNum{0} ; coinNum < duels::COIN_MAX ; ++coinNum )
	{
		assert( coinNum < canCollide.size() );
		if( canCollide[coinNum] && doesMoveObjectCollideWithRect(coinsData[coinNum].move, COIN_RECT, externObjectRect) )
		{
			collision::makeObjectMoveBounceWithRect(coinsData[coinNum].move, COIN_RECT, externObjectRect);
			canCollide[coinNum] = false;
		}
		if( false == canCollide[coinNum] &&
			false == doesMoveObjectCollideWithRect(coinsData[coinNum].move, COIN_RECT, enlargeGivenRect(externObjectRect, SQR_SIZE / 8) ) )
		{
			canCollide[coinNum] = true;
		}
	}
}