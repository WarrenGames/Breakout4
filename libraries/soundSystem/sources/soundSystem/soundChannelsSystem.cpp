#include "soundSystem/soundChannelsSystem.h"
#include "logging/logsStruct.h"
#include "SDL_mixer.h"
#include <string>
#include <sstream>

ChannelsInfos::ChannelsInfos():
	groupTag{-1},
	startChannel{-1},
	endChannel{-1}
{}

SoundChannelsSystem::SoundChannelsSystem(AppLogFiles& logs, const fs::path& channelConfigFilePath):
	isLoadingPerfect{ true }
{
	openFile(logs, channelConfigFilePath);
}

bool SoundChannelsSystem::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

void SoundChannelsSystem::openFile(AppLogFiles& logs, const fs::path& channelConfigFilePath)
{
	if( std::ifstream channelFile{ channelConfigFilePath } )
	{
		readFileLine(logs, channelFile, channelConfigFilePath);
	}
	else{
		isLoadingPerfect = false;
		logs.error.wrFileOpeningError(channelConfigFilePath.string(), "load channel sound system");
	}
}

void SoundChannelsSystem::readFileLine(AppLogFiles& logs, std::ifstream& channelConfigFile, const fs::path& channelConfigFilePath)
{
	std::size_t lineNumber{1};
	std::string fileLine;
	while( std::getline( channelConfigFile, fileLine ) )
	{
		std::istringstream lineStream{ fileLine };
		ChannelsInfos channelInfos{};
		if( lineStream >> channelInfos.groupTag >> channelInfos.startChannel >> channelInfos.endChannel )
		{
			if( channelInfos.endChannel - channelInfos.startChannel + 1 != Mix_GroupChannels(channelInfos.startChannel, channelInfos.endChannel, channelInfos.groupTag) )
			{
				isLoadingPerfect = false;
				logs.error << "Error: couldn't allocate '" << channelInfos.startChannel << "' to '" << channelInfos.endChannel << " channels for group number "
					<< channelInfos.groupTag << ", because: " << Mix_GetError() << " .\n";
			}
		}
		else{
			isLoadingPerfect = false;
			logs.error.wrReadErrorMessage(channelConfigFilePath.string(), "channel start and end values at line " + std::to_string(lineNumber) );
		}
	}
}