#ifndef ONE_PLAYER_RIMS_PAST_H
#define ONE_PLAYER_RIMS_PAST_H

#include <vector>

class OnePlayerRimsPast
{
private:
	std::vector< bool > hasBorderBeenActivated;

public:
	explicit OnePlayerRimsPast();
	~OnePlayerRimsPast() = default;
	OnePlayerRimsPast( const OnePlayerRimsPast& ) = delete;
	OnePlayerRimsPast& operator= ( const OnePlayerRimsPast& ) = delete;
	OnePlayerRimsPast( OnePlayerRimsPast&& ) = default;
	OnePlayerRimsPast& operator= ( OnePlayerRimsPast&& ) = default;
	
	std::size_t size() const;
	void setBorderToActiveOne(std::size_t borderNumber);
	bool wasBorderAlreadyActivated(std::size_t borderNumber) const;
};

#endif //ONE_PLAYER_RIMS_PAST_H