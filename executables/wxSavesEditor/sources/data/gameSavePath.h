#ifndef WX_PREF_PATH_FINDER_H
#define WX_PREF_PATH_FINDER_H

#include "wx/string.h"

class wxPrefPathFinder;

wxString getGameSavesPath(const wxPrefPathFinder& prefPath);

#endif //WX_PREF_PATH_FINDER_H