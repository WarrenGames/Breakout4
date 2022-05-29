#include "contexts/gameStarting/initPrefPath/initPrefPath.h"
#include "prefPath/prefPathFinder.h"
#include "contexts/gameStarting/initSDL2/sdl2_initialization.h"
#include "logging/logsStruct.h"
#include "consts/constPaths.h"
#include "consts/constexprScreen.h"
#include <iostream>

void initPrefPath::startGame()
{
	if( const PrefPathFinder prefPath{COMPANY_NAME, GAME_NAME, SQR_SIZE} )
	{
		initPrefPath::checkPrefPath(prefPath);
	}
	else{
		std::cout << "Error: couldn't find pref path, because: " << prefPath.getError() << std::endl;
	}
}

void initPrefPath::checkPrefPath(const PrefPathFinder& prefPath)
{
	if( AppLogFiles logs{prefPath.getPath(), ERROR_LOG_FILE, WARNING_LOG_FILE} )
	{
		loadSDL2_modules(logs, prefPath);
	}
}
