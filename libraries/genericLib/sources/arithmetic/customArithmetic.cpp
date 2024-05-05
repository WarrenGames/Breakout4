#include "arithmetic/customArithmetic.h"

int getCeilInteger(int numerator, int denominator)
{
	return ( numerator + denominator - 1 ) / denominator;
}

unsigned getPowValue(unsigned x, unsigned y)
{
	unsigned result{1};
	for( unsigned i{0} ; i < y ; ++i )
	{
		result *= x;
	}
	return result;
}