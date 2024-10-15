#include "contexts/gameStarting/initPrefPath/initPrefPath.h"
#include "prefPath/prefPathFinder.h"
#include "contexts/gameStarting/initSDL2/sdl2_initialization.h"
#include "logging/logsStruct.h"
#include "consts/constPaths.h"
#include "consts/constexprScreen.h"
#include <iostream>

void initPrefPath::startGame()
{
	if( const PrefPathFinder prefPath{CompanyName, GameName, SQR_SIZE} )
	{
		initPrefPath::checkPrefPath(prefPath);
	}
	else{
		std::cout << "Error: couldn't find pref path, because: " << prefPath.getError() << '\n';
	}
}

void initPrefPath::checkPrefPath(const PrefPathFinder& prefPath)
{
	if( AppLogFiles logs{prefPath.getPath(), ErrorLogFile, WarningLogFile} )
	{
		loadSDL2_modules(logs, prefPath);
	}
}
