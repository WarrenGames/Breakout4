#include "data/gameSavePath.h"
#include "prefPath/wxPrefPath.h"
#include "consts/constPaths.h"
#include <iostream>

wxString getGameSavesPath(const wxPrefPathFinder& prefPath)
{
	wxString finalPath{ prefPath.getPath() };
	finalPath << SAVE_DIR_NAME;
	finalPath << '/';
	
	return finalPath;
}