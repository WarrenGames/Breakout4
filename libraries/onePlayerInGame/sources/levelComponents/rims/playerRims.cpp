#include "levelComponents/rims/playerRims.h"
#include "consts/rimsConsts.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include <cassert>

constexpr int RimOffY_Position = GameScreenHeight + SQR_SIZE;
constexpr int RimActY_Position = GameScreenHeight - SQR_SIZE;

constexpr int RimSideSize = SQR_SIZE;

OnePlayerRims::OnePlayerRims(Essentials& essentials, int rimsStartState):
	rimTexture{essentials.logs, essentials.rndWnd, "textures/sprites/bricks/purpleRim.png"},
	rimsCoordinates{rims::RimSideNum, rims::RemoveMax},
	activesRimsNumber{rimsStartState},
	rimsMovement{rims::RimIsStatic, rims::RimIsStatic, rims::RimIsStatic},
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
		for( std::size_t i{0} ; i < rims::RemoveMax ; ++i )
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
		case rims::RimIsStatic:
			//Do nothing
			break;
		case rims::RimGoesDown:
			moveRim(rimIndex, 1);
			break;
		case rims::RimGoesUp:
			moveRim(rimIndex, -1);
			break;
		default:
			assert( false && "Error wrong rim state value");
			break;
	}
}

void OnePlayerRims::moveRim(std::size_t rimIndex, int offsetAdd)
{
	assert( rimIndex < rims::RemoveMax );
	rimsCoordinates(rims::LeftRims, rimIndex).y += offsetAdd;
	rimsCoordinates(rims::RightRims, rimIndex).y += offsetAdd;
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
		if( rimsCoordinates(rims::LeftRims, rimNum).y == RimActY_Position )
			rimsMovement[rimNum] = rims::RimIsStatic;
		else if( rimsCoordinates(rims::LeftRims ,rimNum).y > RimActY_Position )
			rimsMovement[rimNum] = rims::RimGoesUp;
	}
	else if( activesRimsNumber > rimNum )
	{
		if( rimsCoordinates(rims::LeftRims, rimNum).y > RimActY_Position )
			rimsMovement[rimNum] = rims::RimGoesUp;
		else if( rimsCoordinates(rims::LeftRims, rimNum).y == RimActY_Position )
			rimsMovement[rimNum] = rims::RimIsStatic;
	}
	else if( activesRimsNumber < rimNum )
	{
		if( rimsCoordinates(rims::LeftRims, rimNum).y < RimOffY_Position )
			rimsMovement[rimNum] = rims::RimGoesDown;
		else if( rimsCoordinates(rims::LeftRims, rimNum).y == RimOffY_Position )
			rimsMovement[rimNum] = rims::RimIsStatic;
	}
}

void OnePlayerRims::initializeOffsets(int rimsStartState)
{
	rimsCoordinates(0, 0) = SDL_Rect{ 0, RimOffY_Position, RimSideSize, RimSideSize};//case 0
	rimsCoordinates(0, 1) = SDL_Rect{ SQR_SIZE, RimOffY_Position, RimSideSize, RimSideSize};//case 2
	rimsCoordinates(0, 2) = SDL_Rect{ SQR_SIZE * 2, RimOffY_Position, RimSideSize, RimSideSize};//case 4
	rimsCoordinates(1, 0) = SDL_Rect{ GameScreenWidth - SQR_SIZE, RimOffY_Position, RimSideSize, RimSideSize};// case 1 
	rimsCoordinates(1, 1) = SDL_Rect{ GameScreenWidth - SQR_SIZE * 2, RimOffY_Position, RimSideSize, RimSideSize};//case 3
	rimsCoordinates(1, 2) = SDL_Rect{ GameScreenWidth - SQR_SIZE * 3, RimOffY_Position, RimSideSize, RimSideSize};//case 5
	
	for( std::size_t i{0} ; i < rims::RemoveMax ; ++i )
	{
		if( rimsStartState >= static_cast<int>(i) )
		{
			rimsCoordinates(0, i).y = RimActY_Position;
			rimsCoordinates(1, i).y = RimActY_Position;
		}
	}
}