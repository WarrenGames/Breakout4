#ifndef BRICK_DATA_H
#define BRICK_DATA_H

struct BrickData
{
	unsigned index;
	unsigned property;
	
	explicit BrickData();
	explicit BrickData(unsigned ind, unsigned prop);
	~BrickData() = default;
	BrickData( const BrickData& ) = default;
	BrickData& operator= ( const BrickData& ) = default;
	
	void set(unsigned newIndex, unsigned newProperty);
};

#endif //BRICK_DATA_H