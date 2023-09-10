#ifndef DUELS_SOUND_LOAD_STRUCTS_H
#define DUELS_SOUND_LOAD_STRUCTS_H

#include "wrappers/mixerPtrWrapper.h"
#include "fileSystem/fileSystem.h"
#include <string>

class LogFile;

struct SoundData
{
	std::string fileLine;
	fs::path soundPath;
	int groupTag;
	unsigned fileLineNumber;
	bool wasLoadingPerfect;
	
	SoundData();
	~SoundData() = default;
	SoundData( const SoundData& ) = delete;
	SoundData& operator= ( const SoundData& ) = delete;
	SoundData( SoundData&& ) = default;
	SoundData& operator= ( SoundData&& ) = default;
};

struct SoundSpecifications
{
	sdl2::Mix_ChunkPtr snd;
	int groupTag;
	
	explicit SoundSpecifications(LogFile& log, const std::string& soundFilePath, int channelGroup);
	~SoundSpecifications() = default;
	SoundSpecifications( const SoundSpecifications& ) = delete;
	SoundSpecifications& operator= ( const SoundSpecifications& ) = delete;
	SoundSpecifications( SoundSpecifications&& ) = default;
	SoundSpecifications& operator= ( SoundSpecifications&& ) = default;
};

struct ChannelData
{
	std::string fileLine;
	int groupTag;
	int firstChannel;
	int lastChannel;
	unsigned fileLineNumber;
	
	explicit ChannelData();
	~ChannelData() = default;
	ChannelData( const ChannelData& ) = delete;
	ChannelData& operator= ( const ChannelData& ) = delete;
	ChannelData( ChannelData&& ) = default;
	ChannelData& operator= ( ChannelData&& ) = default;
};

#endif //DUELS_SOUND_LOAD_STRUCTS_H