#include "generic/sounds/loadChannelsConfig.h"
#include "logging/logsStruct.h"
#include "generic/sounds/soundStructs.h"
#include "SDL_mixer.h"

void loadChanCfg::readLines(AppLogFiles& logs, const fs::path& filePath, bool& channelLoadWasPerfect)
{
	if( std::ifstream channelDataFile{filePath} )
	{
		ChannelData channelData{};
		while( std::getline(channelDataFile, channelData.fileLine) )
		{
			std::istringstream lineStream{channelData.fileLine};
			loadChanCfg::setData(logs, filePath, lineStream, channelData, channelLoadWasPerfect);
			channelData.fileLineNumber++;
		}
	}
	else{
		logs.error.wrFileOpeningError(filePath, "load the channel data");
		channelLoadWasPerfect = false;
	}
}

void loadChanCfg::setData(AppLogFiles& logs, const fs::path& filePath, std::istringstream& lineStream, ChannelData& data, bool& channelLoadWasPerfect)
{
	if( lineStream >> data.groupTag >> data.firstChannel >> data.lastChannel )
	{
		if( data.lastChannel - data.firstChannel + 1 == Mix_GroupChannels(data.firstChannel, data.lastChannel, data.groupTag) )
		{
			logs.warning.wrStringNoEndline("Group tag number ");
			logs.warning.wrUint(data.groupTag);
			logs.warning.wrStringNoEndline(" received with success channels from ");
			logs.warning.wrUint(data.firstChannel);
			logs.warning.wrStringNoEndline(" to ");
			logs.warning.wrUint(data.lastChannel);
			logs.warning.wrStringNoEndline(" .\n");
		}
		else{
			logs.error.wrRessourceInitError("sound channels", Mix_GetError() );
			logs.error.wrStringNoEndline("  Error: with groupTag: ");
			logs.error.wrUint(data.groupTag);
			logs.error.wrStringNoEndline(" first channel: ");
			logs.error.wrUint(data.firstChannel);
			logs.error.wrStringNoEndline(" last channel: ");
			logs.error.wrUint(data.lastChannel);
			logs.error.wrStringNoEndline(" at line number ");
			logs.error.wrUint(data.fileLineNumber);
			logs.error.wrEndLine();
			channelLoadWasPerfect = false;
		}
	}
	else{
		logs.error.wrReadErrorMessage(filePath, "sound channels assignation", data.fileLineNumber);
		channelLoadWasPerfect = false;
	}
}