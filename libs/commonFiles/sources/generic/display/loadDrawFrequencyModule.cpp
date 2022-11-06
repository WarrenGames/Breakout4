#include "generic/display/loadDrawFrequencyModule.h"
#include "prefPath/prefPathFinder.h"
#include "logging/logsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include <string>

constexpr unsigned MicroSecondsDefaultDrawFrequency = 1000 * 1000 / 60;
constexpr unsigned DefaultFramesPerSeconds = 60;

DrawFrequencyModule::DrawFrequencyModule(AppLogFiles& logs, const PrefPathFinder& prefPath):
	refreshTime{ MicroSecondsDefaultDrawFrequency },
	framesPerSecond{ DefaultFramesPerSeconds },
	isLoadingPerfect{true}
{
	openDrawFrequencyFile(logs, prefPath);
}

void DrawFrequencyModule::openDrawFrequencyFile(AppLogFiles& logs, const PrefPathFinder& prefPath)
{
	if( std::ifstream drawFreqFile{ path::getConfigDirFile(prefPath, file::DRAW_FREQ_FILE) } )
	{
		if( drawFreqFile >> framesPerSecond )
		{
			changeFramesPerSecond(framesPerSecond);
			isLoadingPerfect = true;
			logs.warning.wrStringNoEndline("  >> Frames per second was read with success. It's value is ");
			logs.warning.wrUint(framesPerSecond);
			logs.warning.wrStringNoEndline(" .\n");
		}
		else{
			isLoadingPerfect = false;
			logs.error.wrReadErrorMessage(path::getConfigDirFile(prefPath, file::DRAW_FREQ_FILE), "frames per second" );
		}
	}
	else{
		isLoadingPerfect = false;
		logs.error.wrFileOpeningError(path::getConfigDirFile(prefPath, file::DRAW_FREQ_FILE), "read frames per second rate.");
	}
}

DrawFrequencyModule::operator bool() const
{
	return isLoadingPerfect;
}

unsigned DrawFrequencyModule::getFramesPerSecond() const
{
	return framesPerSecond;
}

void DrawFrequencyModule::changeFramesPerSecond(unsigned newFramePerSecondValue)
{
	framesPerSecond = newFramePerSecondValue;
	refreshTime = std::chrono::microseconds{1000 * 1000 / framesPerSecond};
}

bool DrawFrequencyModule::canDrawGame()
{
	if( drawDelay.hasTimeElapsed(std::chrono::microseconds{refreshTime} ) )
	{
		drawDelay.joinTimePoints();
		return true;
	}
	else{
		return false;
	}
}
