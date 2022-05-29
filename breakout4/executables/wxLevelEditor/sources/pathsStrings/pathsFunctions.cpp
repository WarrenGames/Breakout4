#include "pathsStrings/pathsFunctions.h"
#include "prefPath/prefPathFinder.h"
#include "consts/pathsConsts.h"
#include "consts/constexprScreen.h"

std::string pathStr::getPrefPath(const PrefPathFinder& prefPath, const std::string& fileName)
{
	return prefPath.getPath() + fileName;
}