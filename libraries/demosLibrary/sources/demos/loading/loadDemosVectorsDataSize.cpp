#include "demos/loading/loadDemosVectorsDataSize.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "prefPath/prefPathFinder.h"
#include "logging/logsStruct.h"
#include "demos/consts/demosConsts.h"
#include <fstream>

std::size_t demos::getVectorsDataSize(AppLogFiles& logs, const PrefPathFinder& prefPath, const std::string& fileName)
{
	if( std::ifstream configFile{ path::getDemoConfigFile(prefPath, fileName) } )
	{
		std::size_t dataSize{ demos::DefaultReservedDataForRecording };
		if( configFile >> dataSize )
		{
			logs.warning << "The file '" << path::getDemoConfigFile(prefPath, fileName).string() << "' was opened and the read value was " << dataSize << " .\n";
			return dataSize;
		}
		else{
			logs.error << "Error: '" << path::getDemoConfigFile(prefPath, fileName).string() << "' file was opened, but couldn't read demo data size.\n"; 
			return demos::DefaultReservedDataForRecording;
		}
	}
	else{
		logs.error.wrFileOpeningError( path::getDemoConfigFile(prefPath, fileName), "get demo data size for recording" );
		return demos::DefaultReservedDataForRecording;
	}
}