#include "contexts/gameCommon/stalactites/racketFreezesDurationsLoader.h"
#include "types/essentialsStruct.h"
#include <cassert>
#include <fstream>

freezes::FreezeDurations::FreezeDurations(Essentials& essentials, const std::string& configFilePath, std::size_t durationsCount):
	durations(durationsCount),
	wasLoadingPerfect{true}
{
	assert( durationsCount > 0 );
	openConfigFile(essentials, configFilePath, durationsCount);
}

freezes::FreezeDurations::operator bool() const
{
	return wasLoadingPerfect;
}

unsigned freezes::FreezeDurations::getDuration(std::size_t arrayIndex) const
{
	assert( arrayIndex < durations.size() );
	return durations[arrayIndex];
}

std::size_t freezes::FreezeDurations::size() const
{
	return durations.size();
}

void freezes::FreezeDurations::openConfigFile(Essentials& essentials, const std::string& configFilePath, std::size_t durationsCount)
{
	if( std::ifstream configFile{configFilePath} )
	{
		for( auto &duration : durations )
		{
			if( !( configFile >> duration ) )
			{
				essentials.logs.error << "Error: the file '" << configFilePath << "' was open with success but reading failed at a given moment (check there is at least" 
									<< durationsCount << " values in the file.\n";
				wasLoadingPerfect = false;
			}
		}
	}
	else{
		wasLoadingPerfect = false;
		essentials.logs.error << "Error: couldn't load config file for durations: '" << configFilePath << "' with a count of " << durationsCount << " freeze values.\n";
	}
}