#include "levelComponents/balls/ballSpeedsOptions.h"
#include "logging/logsStruct.h"
#include "consts/constexprScreen.h"
#include <cassert>

BallSpeeds::BallSpeeds(AppLogFiles& logs, const std::string& speedsFilePath):
	speeds(onePlGame::SkillLevelMax, 0),
	isLoadingPerfect{true}
{
	if( std::ifstream dataFile{speedsFilePath} )
	{
		for( auto &speed : speeds )
		{
			if( dataFile >> speed )
			{
				speed *= SQR_SIZE;
				speed /= 64.0;
			}
			else
			{
				isLoadingPerfect = false;
				logs.error << "Error: couldn't read speed value in the file: " << speedsFilePath << " .\n";
			}
		}
	}
	else{
		isLoadingPerfect = false;
		logs.error << "Error: couldn't open '" << speedsFilePath << "' file in order to read the speeds value of ball in one player game.\n";
	}
}

bool BallSpeeds::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

double BallSpeeds::getSpeed(std::size_t skillLevel) const
{
	assert( skillLevel < speeds.size() );
	return speeds[skillLevel];
}