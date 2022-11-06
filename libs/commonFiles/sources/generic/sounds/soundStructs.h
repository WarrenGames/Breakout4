#ifndef DUELS_SOUND_LOAD_STRUCTS_H
#define DUELS_SOUND_LOAD_STRUCTS_H

#include "wrappers/sdl2_ptr.h"
#include <string>

class LogFile;

struct SoundData{
	std::string fileLine;
	bool wasLoadingPerfect;
	std::string soundPath;
	int groupTag;
	unsigned fileLineNumber;
	
	SoundData();
};

struct SoundSpecifications
{
	sdl2::Mix_ChunkPtr snd;
	int groupTag;
	
	SoundSpecifications(LogFile& log, const std::string& soundFilePath, int channelGroup);
};

struct ChannelData
{
	std::string fileLine;
	int groupTag;
	int firstChannel;
	int lastChannel;
	unsigned fileLineNumber;
	
	ChannelData();
};

#endif //DUELS_SOUND_LOAD_STRUCTS_H