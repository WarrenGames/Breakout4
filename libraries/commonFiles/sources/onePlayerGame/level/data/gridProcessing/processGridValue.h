#ifndef ONEP_PROCESS_GRID_VALUE_H
#define ONEP_PROCESS_GRID_VALUE_H

#include "consts/onePlayerGridConsts.h"

template<typename T> class MatrixTemp2D;
struct BrickData;

namespace onePlGame{

namespace gridProcess{
	
	unsigned getValue(const MatrixTemp2D<BrickData>& grid);
	
	void actWithBrickType(const BrickData& brickData, unsigned& totalValue);
	
	void actWithGenericBrick(const BrickData& brickData, unsigned& totalValue);
	
	void actWithRichBrick(const BrickData& brickData, unsigned& totalValue);
	
	void actWithBonusCoin(unsigned& totalValue);
	
	void actWithGiftBrick(unsigned& totalValue);
	
	void actWithTenPointsBrick(const BrickData& brickData, unsigned& totalValue);
}

}

#endif //ONEP_PROCESS_GRID_VALUE_H