#include "duels/inGameObjects/bonus/bonusPicker.h"
#include "consts/duelsConstexpr.h"
#include <algorithm>
#include <numeric>
#include <chrono>

BonusPicker::BonusPicker(const std::vector<unsigned>& options):
	bonusPack( std::accumulate(std::cbegin(options), std::cend(options), 0 ) ),
	mersenne{ static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()) },
	tempBonus{0}
{
	fillBonusPack(options);
	nextBonusIt = bonusPack.cbegin();
	tempBonus = *nextBonusIt;
}

unsigned BonusPicker::pickNextBonus()
{
	tempBonus = *nextBonusIt;
	shuffleArray();
	return tempBonus;
}

void BonusPicker::setIteratorToBegin()
{
	nextBonusIt = bonusPack.cbegin();
}

void BonusPicker::fillBonusPack(const std::vector<unsigned>& options)
{
	unsigned sum{0};
	for( unsigned i{0} ; i < options.size() ; ++i )
	{
		for( unsigned j{sum}; j < sum + options[i] ; ++j )
		{
			bonusPack[j] = i;
		}
		sum += options[i];
	}
	std::shuffle(bonusPack.begin(), bonusPack.end(), mersenne);
}

void BonusPicker::shuffleArray()
{
	++nextBonusIt;
	if( nextBonusIt == bonusPack.end() )
	{
		std::shuffle( std::begin(bonusPack), std::end(bonusPack), mersenne);
		nextBonusIt = bonusPack.cbegin();
	}
}