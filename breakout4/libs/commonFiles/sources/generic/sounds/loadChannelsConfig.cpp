#include "generic/sounds/loadChannelsConfig.h"
#include "logging/logFile.h"
#include "generic/sounds/soundStructs.h"
#include "SDL_mixer.h"

void loadChanCfg::readLines(LogFile& log, const std::string& filePath, bool& channelLoadWasPerfect)
{
	if( std::ifstream channelDataFile{filePath} )
	{
		ChannelData channelData{};
		while( std::getline(channelDataFile, channelData.fileLine) )
		{
			std::istringstream lineStream{channelData.fileLine};
			loadChanCfg::setData(log, filePath, lineStream, channelData, channelLoadWasPerfect);
			channelData.fileLineNumber++;
		}
	}
	else{
		log.wrFileOpeningError(filePath, "load the channel data");
		channelLoadWasPerfect = false;
	}
}

void loadChanCfg::setData(LogFile& log, const std::string& filePath, std::istringstream& lineStream, ChannelData& data, bool& channelLoadWasPerfect)
{
	if( lineStream >> data.groupTag >> data.firstChannel >> data.lastChannel )
	{
		if( data.lastChannel - data.firstChannel + 1 == Mix_GroupChannels(data.firstChannel, data.lastChannel, data.groupTag) )
		{
			log.wrStringNoEndline(">> group tag number ");
			log.wrUint(data.groupTag);
			log.wrStringNoEndline(" received with success channels from ");
			log.wrUint(data.firstChannel);
			log.wrStringNoEndline(" to ");
			log.wrUint(data.lastChannel);
			log.wrStringNoEndline(" .\n");
		}
		else{
			log.wrRessourceInitError("sound channels", Mix_GetError() );
			log.wrStringNoEndline("  Error: with groupTag: ");
			log.wrUint(data.groupTag);
			log.wrStringNoEndline(" first channel: ");
			log.wrUint(data.firstChannel);
			log.wrStringNoEndline(" last channel: ");
			log.wrUint(data.lastChannel);
			log.wrStringNoEndline(" at line number ");
			log.wrUint(data.fileLineNumber);
			log.wrEndLine();
			channelLoadWasPerfect = false;
		}
	}
	else{
		log.wrReadErrorMessage(filePath, "sound channels assignation", data.fileLineNumber);
		channelLoadWasPerfect = false;
	}
}