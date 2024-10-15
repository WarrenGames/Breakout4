#ifndef BRICK_DATA_H
#define BRICK_DATA_H

struct BrickData
{
	unsigned index;
	unsigned property;
	
	BrickData();
	BrickData(unsigned ind, unsigned prop);
	~BrickData() = default;
	BrickData( const BrickData& ) = default;
	BrickData& operator= ( const BrickData& ) = default;
	BrickData( BrickData&& ) = default;
	BrickData& operator= ( BrickData&& ) = default;
};

#endif //BRICK_DATA_H