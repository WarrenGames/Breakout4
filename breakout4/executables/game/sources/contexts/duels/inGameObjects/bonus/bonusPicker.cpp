#include "contexts/duels/inGameObjects/bonus/bonusPicker.h"
#include "contexts/duels/duelsConstexpr.h"
#include <algorithm>
#include <numeric>
#include <chrono>

BonusPicker::BonusPicker(const std::vector<unsigned>& options):
	bonusPack( std::accumulate(options.begin(), options.end(), 0 ) ),
	mersenne{ static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()) },
	tempBonus{duels::DB_MAX}
{
	fillBonusPack(options);
	nextBonusIt = bonusPack.begin();
}

unsigned BonusPicker::pickNextBonus()
{
	tempBonus = *nextBonusIt;
	shuffleArray();
	return tempBonus;
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
		std::shuffle(bonusPack.begin(), bonusPack.end(), mersenne);
		nextBonusIt = bonusPack.begin();
	}
}