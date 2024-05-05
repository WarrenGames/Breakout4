#include "duels/instructions/elementsCollisions.h"
#include "spriteMove/objectMove.h"
#include "duels/inGameObjects/bonusCoins/bonusCoin.h"
#include "duels/inGameObjects/balls/duelBall.h"
#include "rectCollisions/processBouncing.h"
#include <cassert>

bool duels::isThisTheSameArrayElement(std::size_t objectA_index, std::size_t objectB_index)
{
	return objectA_index == objectB_index;
}

void duels::resetCoinToCoin(std::size_t coinA_num, ComboCoinData& coinA, std::size_t coinB_num, ComboCoinData& coinB, const SpriteSize& coinRect)
{
	assert( coinA_num < duels::CoinMaxNumber && coinB_num < duels::CoinMaxNumber);
	
	if( false == duels::isThisTheSameArrayElement(coinA_num, coinB_num) && coinA.collision.isEffective && coinB.collision.isEffective )
	{
		if( false == coinA.collision.checkWCoinCollision[coinB_num] && false == coinB.collision.checkWCoinCollision[coinA_num] )
		{
			if( false == bouncing::objectsCollide(coinA.move, coinRect, coinB.move, coinRect, duels::SizeDecalCollideBox) )
			{
				coinA.collision.checkWCoinCollision[coinB_num] = true;
				coinB.collision.checkWCoinCollision[coinA_num] = true;
			}
		}
	}
}

void duels::resetCoinToBall(std::size_t coin_num, ComboCoinData& coin, const SpriteSize& coinSize, std::size_t ball_num, ComboBallData& ball, const SpriteSize& ballSize)
{
	assert( coin_num < duels::CoinMaxNumber && ball_num < duels::BallMaxNumber );
	
	if( coin.collision.isEffective && ball.collision.isEffective )
	{
		if( false == coin.collision.checkWBallCollision[ball_num] && false == ball.collision.checkWCoinCollision[coin_num] )
		{
			if( false == bouncing::objectsCollide(coin.move, coinSize, ball.move, ballSize, duels::SizeDecalCollideBox) )
			{
				coin.collision.checkWBallCollision[ball_num] = true;
				ball.collision.checkWCoinCollision[coin_num] = true;
			}
		}
	}
}

void duels::resetBallToBall(std::size_t ballA_num, ComboBallData& ballA, std::size_t ballB_num, ComboBallData& ballB, const SpriteSize& ballRect)
{
	assert( ballA_num < duels::BallMaxNumber && ballB_num < duels::BallMaxNumber );
	
	if( false == duels::isThisTheSameArrayElement(ballA_num, ballB_num) && ballA.collision.isEffective && ballB.collision.isEffective )
	{
		if( false == ballA.collision.checkWBallCollision[ballB_num] && false == ballB.collision.checkWBallCollision[ballA_num] )
		{
			if( false == bouncing::objectsCollide(ballA.move, ballRect, ballB.move, ballRect, duels::SizeDecalCollideBox) )
			{
				ballA.collision.checkWBallCollision[ballB_num] = true;
				ballB.collision.checkWBallCollision[ballA_num] = true;
			}
		}
	}
}

void duels::coinToCoinBouncing(std::size_t coinA_num, ComboCoinData& coinA, std::size_t coinB_num, ComboCoinData& coinB, const SpriteSize& coinTextureSize)
{
	assert( coinA_num < duels::CoinMaxNumber && coinB_num < duels::CoinMaxNumber );
	
	if( false == duels::isThisTheSameArrayElement(coinA_num, coinB_num) 
		&& coinA.collision.isEffective && coinB.collision.isEffective 
		&& coinA.collision.checkWCoinCollision[coinB_num] && coinB.collision.checkWCoinCollision[coinA_num] )
	{
		if( bouncing::objectsCollide(coinA.move, coinTextureSize, coinB.move, coinTextureSize, 0) )
		{
			bouncing::processElementsBouncing(coinA.move, coinB.move, coinTextureSize);
			coinA.collision.checkWCoinCollision[coinB_num] = false;
			coinB.collision.checkWCoinCollision[coinA_num] = false;
		}
	}
}

void duels::coinToBallBouncing(std::size_t coin_num, ComboCoinData& coin, const SpriteSize& coinTextureSize, std::size_t ball_num, ComboBallData& ball, const SpriteSize& ballTextureSize)
{
	assert( coin_num < duels::CoinMaxNumber && ball_num < duels::BallMaxNumber );
	
	if( coin.collision.isEffective && ball.collision.isEffective && coin.collision.checkWBallCollision[ball_num] && ball.collision.checkWCoinCollision[coin_num] )
	{
		if( bouncing::objectsCollide(coin.move, coinTextureSize, ball.move, ballTextureSize, 0) )
		{
			bouncing::processElementsBouncing(coin.move, ball.move, ballTextureSize);
			coin.collision.checkWBallCollision[ball_num] = false;
			ball.collision.checkWCoinCollision[coin_num] = false;
		}
	}
}

void duels::ballToBallBouncing(std::size_t ballA_num, ComboBallData& ballA, std::size_t ballB_num, ComboBallData& ballB, const SpriteSize& ballTextureSize)
{
	assert( ballA_num < duels::BallMaxNumber && ballB_num < duels::BallMaxNumber );
	
	if( false == duels::isThisTheSameArrayElement(ballA_num, ballB_num) 
		&& ballA.collision.isEffective && ballB.collision.isEffective 
		&& ballA.collision.checkWBallCollision[ballB_num] && ballB.collision.checkWBallCollision[ballA_num] )
	{
		if( bouncing::objectsCollide(ballA.move, ballTextureSize, ballB.move, ballTextureSize, 0) )
		{
			bouncing::processElementsBouncing(ballA.move, ballB.move, ballTextureSize);
			ballA.collision.checkWBallCollision[ballB_num] = false;
			ballB.collision.checkWBallCollision[ballA_num] = false;
			
		}
	}
}

SDL_Rect duels::enlargeGivenRect(const SDL_Rect& rect, int interval)
{
	return SDL_Rect{ rect.x - interval, rect.y - interval, rect.w + interval * 2, rect.h + interval * 2};
}
