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
		case bricks::index::GenericBrick:
			onePlGame::gridProcess::actWithGenericBrick(brickData, totalValue);
			break;
		case bricks::index::RichBrick:
			onePlGame::gridProcess::actWithRichBrick(brickData, totalValue);
			break;
		case bricks::index::BonusCoin:
			onePlGame::gridProcess::actWithBonusCoin(totalValue);
			break;
		case bricks::index::GiftBrick:
			onePlGame::gridProcess::actWithGiftBrick(totalValue);
			break;
		case bricks::index::TenPointsBrick:
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
		case bricks::RichBrick::SteelLeft:
			totalValue += 50;
			break;
		case bricks::RichBrick::BronzeLeft:
			totalValue += 100;
			break;
		case bricks::RichBrick::SilverLeft:
			totalValue += 200;
			break;
		case bricks::RichBrick::GoldLeft:
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