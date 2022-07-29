#ifndef BRICK_DATA_H
#define BRICK_DATA_H

struct BrickData
{
	unsigned index;
	unsigned property;
	
	BrickData();
	BrickData(unsigned ind, unsigned prop);
	
	void set(unsigned newIndex, unsigned newProperty);
};

#endif //BRICK_DATA_H