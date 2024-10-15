#ifndef ONE_PLAYER_GAME_RIMS_SCORE_STOCK_H
#define ONE_PLAYER_GAME_RIMS_SCORE_STOCK_H

#include <vector>

class RimsScoreStock
{
private:
	std::vector< int > scoresValues;
	int rimsScoreReserve;

public:
	RimsScoreStock();
	~RimsScoreStock() = default;
	RimsScoreStock( const RimsScoreStock& ) = delete;
	RimsScoreStock& operator= ( const RimsScoreStock& ) = delete;
	RimsScoreStock( RimsScoreStock&& ) = default;
	RimsScoreStock& operator= ( RimsScoreStock&& ) = default;
	
	void stockGivenScore(std::size_t scoreIndex);
	int getReservedScoreIfAny();
	void stockDefaultScore();
	
	int getGivenRimScore(std::size_t scoreIndex) const;
	std::size_t size() const;
};

#endif //ONE_PLAYER_GAME_RIMS_SCORE_STOCK_H