#include "levelComponents/rims/rimsScoreStock.h"
#include "consts/rimsConsts.h"
#include <cassert>

RimsScoreStock::RimsScoreStock():
	scoresValues{ rims::FirstRimBonus, rims::SecondRimBonus, rims::ThirdRimBonus, rims::LatterRimBonus },
	rimsScoreReserve{ 0 }
{
	
}

void RimsScoreStock::stockGivenScore(std::size_t scoreIndex)
{
	assert( scoreIndex < scoresValues.size());
	rimsScoreReserve += scoresValues[scoreIndex];
}

void RimsScoreStock::stockDefaultScore()
{
	rimsScoreReserve += scoresValues.back();
}

int RimsScoreStock::getReservedScoreIfAny()
{
	if( rimsScoreReserve == 0 )
	{
		return 0;
	}
	else{
		int temp{ rimsScoreReserve };
		rimsScoreReserve = 0;
		return temp;
	}
}

int RimsScoreStock::getGivenRimScore(std::size_t scoreIndex) const
{
	assert( scoreIndex < scoresValues.size() );
	return scoresValues[scoreIndex];
}

std::size_t RimsScoreStock::size() const
{
	return scoresValues.size();
}