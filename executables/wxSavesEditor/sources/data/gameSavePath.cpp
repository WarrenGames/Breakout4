#include "data/gameSavePath.h"
#include "prefPath/wxPrefPath.h"
#include "consts/constPaths.h"
#include <iostream>

fs::path getGameSavesPath(const wxPrefPathFinder& prefPath)
{
	fs::path finalPath{ prefPath.getFsPath() };
	finalPath /= GameSavesDirectory;
	
	return finalPath;
}