#include "types/essentialsStruct.h"
#include "logging/logFile.h"
#include <string>

Essentials::Essentials(AppLogFiles& logs_, const PrefPathFinder& prefPathFinder, const std::string& chosenLanguage, sdl2::RendererWindow& rendererWindow, input::User& userInput):
	logs{logs_},
	prefPath{prefPathFinder},
	language{chosenLanguage},
	rndWnd{rendererWindow},
	inp{userInput},
	drawFreq{logs_, prefPathFinder}
{
	
}