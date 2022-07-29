#ifndef BRICK_DATA_H
#define BRICK_DATA_H

struct BrickData
{
	unsigned index;
	unsigned property;
	
	BrickData();
	BrickData(unsigned ind, unsigned prop);
};

#endif //BRICK_DATA_H