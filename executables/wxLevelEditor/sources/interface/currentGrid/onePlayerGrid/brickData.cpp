#include "interface/currentGrid/onePlayerGrid/brickData.h"

BrickData::BrickData():
	index{0},
	property{0}
{

}

BrickData::BrickData(unsigned ind, unsigned prop):
	index{ind}, 
	property{prop}
{

}

void BrickData::set(unsigned newIndex, unsigned newProperty)
{
	index = newIndex;
	property = newProperty;
}