#ifndef TEMPLATE_LOGGING_H
#define TEMPLATE_LOGGING_H

#include "logging/logFile.h"

template<typename T>
void logLoadingStatus(LogFile& logFile, const std::string& dataName, T& data)
{
	logFile << "Loading status of " + dataName + " : ";
	if( data.wasLoadingPerfect() )
	{
		logFile << "1\n";
	}
	else{
		logFile << "0\n";
	}
}


#endif //TEMPLATE_LOGGING_H