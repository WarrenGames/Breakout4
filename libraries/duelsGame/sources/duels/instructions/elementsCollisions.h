#ifndef DUELS_ELEMENTS_COLLISIONS_H
#define DUELS_ELEMENTS_COLLISIONS_H

#include "consts/duelsConstexpr.h"
#include "customTypes/positionTypes.h"
#include "types/spriteSize.h"

namespace spriteMove{ class ObjectMoving; }
struct SpriteSize;

namespace duels{

struct ComboBallData;
struct ComboCoinData;
	
constexpr SpriteSize CoinRect = { CoinTextureSize, CoinTextureSize };
constexpr SpriteSize BallRect = { BallTextureSize, BallTextureSize };

bool isThisTheSameArrayElement(std::size_t objectA_index, std::size_t objectB_index);

void resetCoinToCoin(std::size_t coinA_num, duels::ComboCoinData& coinA, std::size_t coinB_num, duels::ComboCoinData& coinB, const SpriteSize& coinTextureSize);

void resetCoinToBall(std::size_t coin_num, duels::ComboCoinData& coin, const SpriteSize& coinTextureSize, std::size_t ball_num, duels::ComboBallData& ball, const SpriteSize& ballTextureSize);

void resetBallToBall(std::size_t ballA_num, duels::ComboBallData& ballA, std::size_t ballB_num, duels::ComboBallData& ballB, const SpriteSize& ballTextureSize);

void coinToCoinBouncing(std::size_t coinA_num, duels::ComboCoinData& coinA, std::size_t coinB_num, duels::ComboCoinData& coinB, const SpriteSize& coinTextureSize);

void coinToBallBouncing(std::size_t coin_num, duels::ComboCoinData& coin, const SpriteSize& coinTextureSize, std::size_t ball_num, duels::ComboBallData& ball, const SpriteSize& ballTextureSize);

void ballToBallBouncing(std::size_t ballA_num, duels::ComboBallData& ballA, std::size_t ballB_num, duels::ComboBallData& ballB, const SpriteSize& ballTextureSize);

SDL_Rect enlargeGivenRect(const SDL_Rect& rect, int interval);

}

#endif //DUELS_ELEMENTS_COLLISIONS_H