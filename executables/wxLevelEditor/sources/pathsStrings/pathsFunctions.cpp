#include "pathsStrings/pathsFunctions.h"
#include "prefPath/wxPrefPath.h"
#include "consts/pathsConsts.h"
#include "consts/constexprScreen.h"

wxString pathStr::getPrefPath(const wxPrefPathFinder& prefPath, const wxString& fileName)
{
	return prefPath.getPath() + fileName;
}