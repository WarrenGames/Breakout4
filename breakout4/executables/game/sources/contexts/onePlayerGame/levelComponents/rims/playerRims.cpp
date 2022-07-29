#include "contexts/onePlayerGame/levelComponents/rims/playerRims.h"
#include "consts/rimsConsts.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include <cassert>

constexpr int RIM_OFF_YPOS = GAME_SCREEN_HEIGHT + SQR_SIZE;
constexpr int RIM_ACT_YPOS = GAME_SCREEN_HEIGHT - SQR_SIZE;

constexpr int RIM_SIDE_SIZE = SQR_SIZE;

OnePlayerRims::OnePlayerRims(Essentials& essentials, int rimsStartState):
	rimTexture{essentials.logs, essentials.rndWnd, "textures/sprites/bricks/purpleRim.png"},
	rimsCoordinates{rims::RIM_SIDE_NUM, rims::RIM_MAX},
	activesRimsNumber{rimsStartState},
	rimsMovement{rims::RIM_IS_STATIC, rims::RIM_IS_STATIC, rims::RIM_IS_STATIC},
	rimMovementDelay{}
{
	initializeOffsets(rimsStartState);
}

void OnePlayerRims::update()
{
	moveActiveRims();
	watchStatus();
}

int OnePlayerRims::getRimsStatus() const
{
	return activesRimsNumber;
}

void OnePlayerRims::changeStatus(int change)
{
	assert( change == -1 || change == 1 );
	activesRimsNumber += change;
}

void OnePlayerRims::drawEverything(Essentials& essentials)
{
	for( auto const &rimOffset : rimsCoordinates )
	{
		rimTexture.draw(essentials.rndWnd, rimOffset.x, rimOffset.y);
	}
}

std::vector<SDL_Rect>::const_iterator OnePlayerRims::begin() const
{
	return rimsCoordinates.begin();
}

std::vector<SDL_Rect>::const_iterator OnePlayerRims::end() const
{
	return rimsCoordinates.end();
}

void OnePlayerRims::moveActiveRims()
{
	if( rimMovementDelay.hasTimeElapsed( std::chrono::milliseconds{2000 / SQR_SIZE / 2} ) )
	{
		for( std::size_t i{0} ; i < rims::RIM_MAX ; ++i )
		{
			actWithRimStatus(i);
		}
		rimMovementDelay.joinTimePoints();
	}
}

void OnePlayerRims::actWithRimStatus(std::size_t rimIndex)
{
	switch( rimsMovement[rimIndex] )
	{
		case rims::RIM_IS_STATIC:
			//Do nothing
			break;
		case rims::RIM_GOES_DOWN:
			moveRim(rimIndex, 1);
			break;
		case rims::RIM_GOES_UP:
			moveRim(rimIndex, -1);
			break;
		default:
			assert( false && "Error wrong rim state value");
			break;
	}
}

void OnePlayerRims::moveRim(std::size_t rimIndex, int offsetAdd)
{
	assert( rimIndex < rims::RIM_MAX );
	rimsCoordinates(rims::LEFT_RIMS, rimIndex).y += offsetAdd;
	rimsCoordinates(rims::RIGHT_RIMS, rimIndex).y += offsetAdd;
}

void OnePlayerRims::watchStatus()
{
	for( int rimNum{0} ; rimNum < static_cast<int>(rimsMovement.size()) ; ++rimNum )
	{
		setRimMoveType(rimNum);
	}
}

void OnePlayerRims::setRimMoveType(int rimNum)
{
	if( activesRimsNumber == rimNum )
	{
		if( rimsCoordinates(rims::LEFT_RIMS, rimNum).y == RIM_ACT_YPOS )
			rimsMovement[rimNum] = rims::RIM_IS_STATIC;
		else if( rimsCoordinates(rims::LEFT_RIMS ,rimNum).y > RIM_ACT_YPOS )
			rimsMovement[rimNum] = rims::RIM_GOES_UP;
	}
	else if( activesRimsNumber > rimNum )
	{
		if( rimsCoordinates(rims::LEFT_RIMS, rimNum).y > RIM_ACT_YPOS )
			rimsMovement[rimNum] = rims::RIM_GOES_UP;
		else if( rimsCoordinates(rims::LEFT_RIMS, rimNum).y == RIM_ACT_YPOS )
			rimsMovement[rimNum] = rims::RIM_IS_STATIC;
	}
	else if( activesRimsNumber < rimNum )
	{
		if( rimsCoordinates(rims::LEFT_RIMS, rimNum).y < RIM_OFF_YPOS )
			rimsMovement[rimNum] = rims::RIM_GOES_DOWN;
		else if( rimsCoordinates(rims::LEFT_RIMS, rimNum).y == RIM_OFF_YPOS )
			rimsMovement[rimNum] = rims::RIM_IS_STATIC;
	}
}

void OnePlayerRims::initializeOffsets(int rimsStartState)
{
	rimsCoordinates(0, 0) = SDL_Rect{ 0, RIM_OFF_YPOS, RIM_SIDE_SIZE, RIM_SIDE_SIZE};//case 0
	rimsCoordinates(0, 1) = SDL_Rect{ SQR_SIZE, RIM_OFF_YPOS, RIM_SIDE_SIZE, RIM_SIDE_SIZE};//case 2
	rimsCoordinates(0, 2) = SDL_Rect{ SQR_SIZE * 2, RIM_OFF_YPOS, RIM_SIDE_SIZE, RIM_SIDE_SIZE};//case 4
	rimsCoordinates(1, 0) = SDL_Rect{ GAME_SCREEN_WIDTH - SQR_SIZE, RIM_OFF_YPOS, RIM_SIDE_SIZE, RIM_SIDE_SIZE};// case 1 
	rimsCoordinates(1, 1) = SDL_Rect{ GAME_SCREEN_WIDTH - SQR_SIZE * 2, RIM_OFF_YPOS, RIM_SIDE_SIZE, RIM_SIDE_SIZE};//case 3
	rimsCoordinates(1, 2) = SDL_Rect{ GAME_SCREEN_WIDTH - SQR_SIZE * 3, RIM_OFF_YPOS, RIM_SIDE_SIZE, RIM_SIDE_SIZE};//case 5
	
	for( std::size_t i{0} ; i < rims::RIM_MAX ; ++i )
	{
		if( rimsStartState >= static_cast<int>(i) )
		{
			rimsCoordinates(0, i).y = RIM_ACT_YPOS;
			rimsCoordinates(1, i).y = RIM_ACT_YPOS;
		}
	}
}