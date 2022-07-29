#include "onePlayerGame/level/data/gridProcessing/processGridValue.h"
#include "matrices/matrix2D.h"
#include "types/brickData.h"
#include <algorithm>

unsigned onePlGame::gridProcess::getValue(const MatrixTemp2D<BrickData>& grid)
{
	unsigned totalValue{0};
	
	std::for_each( std::cbegin(grid), std::cend(grid), [&totalValue](auto &brickData){ actWithBrickType(brickData, totalValue); } );
	
	return totalValue;
}

void onePlGame::gridProcess::actWithBrickType(const BrickData& brickData, unsigned& totalValue)
{
	switch( brickData.index )
	{
		case BRICKS::INDEX::GEN_BRICK:
			onePlGame::gridProcess::actWithGenericBrick(brickData, totalValue);
			break;
		case BRICKS::INDEX::RICH_BRICK:
			onePlGame::gridProcess::actWithRichBrick(brickData, totalValue);
			break;
		case BRICKS::INDEX::BONUS_COIN:
			onePlGame::gridProcess::actWithBonusCoin(totalValue);
			break;
		case BRICKS::INDEX::GIFT_BRICK:
			onePlGame::gridProcess::actWithGiftBrick(totalValue);
			break;
		case BRICKS::INDEX::TEN_POINTS:
			onePlGame::gridProcess::actWithTenPointsBrick(brickData, totalValue);
			break;
	}
}

void onePlGame::gridProcess::actWithGenericBrick(const BrickData& brickData, unsigned& totalValue)
{
	totalValue += ( brickData.property + 1 ) * 10;
}

void onePlGame::gridProcess::actWithRichBrick(const BrickData& brickData, unsigned& totalValue)
{
	switch( brickData.property )
	{
		case BRICKS::RICH::STEEL_LEFT:
			totalValue += 50;
			break;
		case BRICKS::RICH::BRONZE_LEFT:
			totalValue += 100;
			break;
		case BRICKS::RICH::SILVER_LEFT:
			totalValue += 200;
			break;
		case BRICKS::RICH::GOLD_LEFT:
			totalValue += 400;
			break;
	}
}

void onePlGame::gridProcess::actWithBonusCoin(unsigned& totalValue)
{
	totalValue += 10;
}

void onePlGame::gridProcess::actWithGiftBrick(unsigned& totalValue)
{
	totalValue += 10;
}

void onePlGame::gridProcess::actWithTenPointsBrick(const BrickData& brickData, unsigned& totalValue)
{
	totalValue += -10 * brickData.property + 80;
}