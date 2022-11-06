#include "arithmetic/customArithmetic.h"

int getCeilInteger(int numerator, int denominator)
{
	return ( numerator + denominator - 1 ) / denominator;
}
