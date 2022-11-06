#include "contexts/duels/zones/metalStrings/subObjects/verticalBarriersDrawing.h"
#include "types/essentialsStruct.h"
#include <cassert>

VerticalBarrierDrawing::VerticalBarrierDrawing(Essentials& essentials, const std::vector<Offset>& barriersPositions):
	positions{barriersPositions},
	verticalBarrier{essentials.logs, essentials.rndWnd, "textures/gameZones/factory/partition.png"}
{
	
}

void VerticalBarrierDrawing::drawBarriers(Essentials& essentials)
{
	if( false == positions.empty() )
	{
		for( auto const &barrier : positions )
		{
			verticalBarrier.draw(essentials.rndWnd, barrier.x, barrier.y);
		}
	}
}

void VerticalBarrierDrawing::moveUpBarrier(std::size_t barrierNumber)
{
	assert( barrierNumber < positions.size() );
	positions[barrierNumber].y -= 1;
}

void VerticalBarrierDrawing::moveDownBarrier(std::size_t barrierNumber)
{
	assert( barrierNumber < positions.size() );
	positions[barrierNumber].y += 1;
}

const Offset& VerticalBarrierDrawing::getBarrierPosition(std::size_t playerNum) const
{
	assert( playerNum < positions.size() );
	return positions[playerNum];
}

SDL_Rect VerticalBarrierDrawing::getRect(std::size_t barrierNum) const
{
	assert( barrierNum < positions.size() );
	return SDL_Rect{ positions[barrierNum].x, positions[barrierNum].y, verticalBarrier.sprite.width(), verticalBarrier.sprite.height() };
}

std::size_t VerticalBarrierDrawing::size() const
{
	return positions.size();
}