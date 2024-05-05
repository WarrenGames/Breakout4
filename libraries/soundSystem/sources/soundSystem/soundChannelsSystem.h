#ifndef SOUND_CHANNELS_SYSTEM_H
#define SOUND_CHANNELS_SYSTEM_H

/*
	SoundChannelSystem class's purpose is to configure the groups of sound playing 
		according to the available channels. In order to achieve this, it ideally
		reads a file ('channelConfigFilePath' parameter) that contains at each line
		a given group tag then the interval of the channel it depends on, with two numbers
		the starting channel and the end channel (included).
		File line example:
		8 12 16
		Here the group tag 8 will use the channels from 12 to 16 (so five sounds on group tag 8
		will be playable at the same time).
		Later on in the game, you will be able to play a given sound (by its index on a group tag
		with the SoundPlayer class with this member function:
		"void playSoundOnGroup(unsigned soundIndex, unsigned group) const;"
  
*/
 
#include "fileSystem/fileSystem.h"
#include <iosfwd>

struct AppLogFiles;

struct ChannelsInfos
{
	int groupTag;
	int startChannel;
	int endChannel;
	
	ChannelsInfos();
	~ChannelsInfos() = default;
	ChannelsInfos( const ChannelsInfos& ) = default;
	ChannelsInfos& operator= ( const ChannelsInfos& ) = default;
};

class SoundChannelsSystem
{
private:
	bool isLoadingPerfect;

public:
	explicit SoundChannelsSystem(AppLogFiles& logs, const fs::path& channelConfigFilePath);
	~SoundChannelsSystem() = default;
	SoundChannelsSystem( const SoundChannelsSystem& ) = delete;
	SoundChannelsSystem& operator= ( const SoundChannelsSystem& ) = delete;
	SoundChannelsSystem( SoundChannelsSystem&& ) = default;
	SoundChannelsSystem& operator= ( SoundChannelsSystem&& ) = default;

	bool wasLoadingPerfect() const;

private:
	void openFile(AppLogFiles& logs, const fs::path& channelConfigFilePath);
	void readFileLine(AppLogFiles& logs, std::ifstream& channelConfigFile, const fs::path& channelConfigFilePath);

};

#endif //SOUND_CHANNELS_SYSTEM_H