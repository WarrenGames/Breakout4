#ifndef ONEP_PROCESS_GRID_VALUE_H
#define ONEP_PROCESS_GRID_VALUE_H

#include "consts/onePlayerGridConsts.h"

template<typename T> class MatrixTemp2D;
struct BrickData;

namespace onePlGame{

namespace gridProcess{
	
	int getValue(const MatrixTemp2D<BrickData>& grid);
	
	void actWithBrickType(const BrickData& brickData, int& totalValue);
	
	void actWithGenericBrick(const BrickData& brickData, int& totalValue);
	
	void actWithRichBrick(const BrickData& brickData, int& totalValue);
	
	void actWithBonusCoin(int& totalValue);
	
	void actWithGiftBrick(int& totalValue);
	
	void actWithTenPointsBrick(const BrickData& brickData, int& totalValue);
}

}

#endif //ONEP_PROCESS_GRID_VALUE_H