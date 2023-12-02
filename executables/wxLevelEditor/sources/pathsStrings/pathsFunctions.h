#ifndef PATHS_FUNCTIONS_H
#define PATHS_FUNCTIONS_H

#include <wx/string.h>

class wxPrefPathFinder;

namespace pathStr{

wxString getPrefPath(const wxPrefPathFinder& prefPath, const wxString& fileName);

}

#endif //PATHS_FUNCTIONS_H