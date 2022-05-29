#include "generic/sounds/soundStructs.h"
#include "logging/logFile.h"
#include "sounds/loadSound.h"

SoundData::SoundData():
	wasLoadingPerfect{true},
	groupTag{-1},
	fileLineNumber{1}
{

}

SoundSpecifications::SoundSpecifications(LogFile& log, const std::string& soundFilePath, int channelGroup):
	snd{ loadSoundChunk(log, "sounds/" + soundFilePath) },
	groupTag{channelGroup}
{
	
}

ChannelData::ChannelData():
	groupTag{-1},
	firstChannel{-1},
	lastChannel{-1},
	fileLineNumber{1}
{
	
}