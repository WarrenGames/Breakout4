#ifndef ESSENTIALS_STRUCT_H
#define ESSENTIALS_STRUCT_H

#include "logging/logsStruct.h"
#include "prefPath/prefPathFinder.h"
#include "generic/input/userInput.h"
#include "texturing/rendererWindow.h"
#include "generic/display/loadDrawFrequencyModule.h"

struct Essentials
{
	AppLogFiles& logs;
	const PrefPathFinder& prefPath;
	const std::string& language;
	sdl2::RendererWindow& rndWnd;
	input::User& inp;
	DrawFrequencyModule drawFreq;
	
	explicit Essentials(AppLogFiles& logs_, const PrefPathFinder& prefPathFinder, const std::string& chosenLanguage, sdl2::RendererWindow& rendererWindow, input::User& userInput);
};

#endif //ESSENTIALS_STRUCT_H