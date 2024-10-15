#ifndef ONE_PLAYER_BALL_SPEEDS_OPTIONS_H
#define ONE_PLAYER_BALL_SPEEDS_OPTIONS_H

#include "consts/onePlayerLevelConsts.h"
#include <vector>
#include <string>

struct AppLogFiles;

class BallSpeeds
{
private:
	std::vector< double > speeds;
	bool isLoadingPerfect;

public:
	explicit BallSpeeds(AppLogFiles& logs, const std::string& speedsFilePath);
	~BallSpeeds() = default;
	BallSpeeds( const BallSpeeds& ) = delete;
	BallSpeeds& operator= ( const BallSpeeds& ) = delete;
	BallSpeeds( BallSpeeds&& ) = default;
	BallSpeeds& operator= ( BallSpeeds&& ) = default;
	
	bool wasLoadingPerfect() const;
	
	double getSpeed(std::size_t skillLevel) const;
};

#endif //ONE_PLAYER_BALL_SPEEDS_OPTIONS_H