#ifndef WX_PREF_PATH_FINDER_H
#define WX_PREF_PATH_FINDER_H

#include "fileSystem/fileSystem.h"

class wxPrefPathFinder;

fs::path getGameSavesPath(const wxPrefPathFinder& prefPath);

#endif //WX_PREF_PATH_FINDER_H