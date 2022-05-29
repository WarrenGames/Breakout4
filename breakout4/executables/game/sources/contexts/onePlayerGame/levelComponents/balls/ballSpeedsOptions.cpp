#include "contexts/onePlayerGame/levelComponents/balls/ballSpeedsOptions.h"
#include "logging/logsStruct.h"

BallSpeeds::BallSpeeds(AppLogFiles& logs, const std::string& speedsFilePath):
	isLoadingPerfect{true},
	speeds{3, 4, 5}
{
	if( std::ifstream dataFile{speedsFilePath} )
	{
		for( auto &speed : speeds )
		{
			if( ! ( dataFile >> speed ) )
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