#include "spriteMove/orientation.h"
#include "spriteMove/pi.h"
#include <cmath>

long int spriteMove::getDirection(int directionNumber, int xVect, int yVect)
{
	double xRatio{static_cast<double>(xVect)};
	double yRatio{static_cast<double>(yVect)};
	//First quarter
	if(xVect > 0 && -(yVect) > 0 )
	{
		return std::lround( directionNumber / 2 / M_PI * std::atan(-yRatio / xRatio) );
	}
	//Second quarter
	else if(xVect < 0 && -(yVect) > 0 )
	{
		 return std::lround( directionNumber / 2 / M_PI * std::atan(-yRatio / xRatio) + directionNumber / 2 );
	}
	//Third quarter
	else if(xVect < 0 && -(yVect) < 0 )
	{
		return std::lround( directionNumber / 2 / M_PI * std::atan(-yRatio / xRatio) + directionNumber  / 2 );
	}
	//Forth quarter
	else if(xVect > 0 && -(yVect) < 0 )
	{
		return std::lround( directionNumber / 2 / M_PI * std::atan(-yRatio / xRatio) + directionNumber ) % directionNumber;
	}
	//With x equal to 0
	else if( xVect == 0 && -(yVect) > 0)
	{
		return directionNumber / 4 ;
	}
	else if( xVect == 0 && -(yVect) < 0)
	{
		return directionNumber * 3 / 4 ;
	}
	//With y equal to 0
	else if( xVect > 0 && -(yVect) == 0 )
	{
		return 0;
	}
	else if( xVect < 0 && -(yVect) == 0 )
	{
		return directionNumber / 2;
	}
	else{
		return 0;
	}
}

Offset spriteMove::getDirectionVectors(int directionsNumber, int direction, int squareSize)
{
	double radAngle{ direction * 2 * M_PI / directionsNumber };
	
	return Offset{ 
		static_cast<int>(squareSize * 8 * std::cos(radAngle) ), 
		static_cast<int>(squareSize * 8 * -std::sin(radAngle) ) };
}