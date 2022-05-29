#ifndef ONE_PLAYER_BALL_SPEEDS_OPTIONS_H
#define ONE_PLAYER_BALL_SPEEDS_OPTIONS_H

#include "consts/onePlayerLevelConsts.h"
#include <array>
#include <string>

struct AppLogFiles;

struct BallSpeeds
{
	bool isLoadingPerfect;
	std::array< double, onePlGame::SKILL_LEVEL_MAX > speeds;
	
	explicit BallSpeeds(AppLogFiles& logs, const std::string& speedsFilePath);
	~BallSpeeds() = default;
	BallSpeeds( const BallSpeeds& ) = delete;
	BallSpeeds& operator= ( const BallSpeeds& ) = delete;
	BallSpeeds( BallSpeeds&& ) = default;
	BallSpeeds& operator= ( BallSpeeds&& ) = default;
};

#endif //ONE_PLAYER_BALL_SPEEDS_OPTIONS_H