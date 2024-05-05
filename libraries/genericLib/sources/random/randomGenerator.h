#ifndef GENERIC_INTEGER_RANDOM_GENERATOR_H
#define GENERIC_INTEGER_RANDOM_GENERATOR_H

#include <random>

class IntRandomGenerator
{
private:
	std::mt19937 mersenne;
	std::uniform_int_distribution<int> integers;
	
public:
	explicit IntRandomGenerator(int lowValue, int highValue);
	explicit IntRandomGenerator(int lowValue, int highValue, unsigned seedAdd);
	~IntRandomGenerator() = default;
	IntRandomGenerator( const IntRandomGenerator& ) = delete;
	IntRandomGenerator& operator= ( const IntRandomGenerator& ) = delete;
	IntRandomGenerator( IntRandomGenerator&& ) = default;
	IntRandomGenerator& operator= ( IntRandomGenerator&& ) = default;
	
	int getRandomValue();
};

#endif //GENERIC_INTEGER_RANDOM_GENERATOR_H