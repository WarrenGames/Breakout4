#ifndef PATHS_FUNCTIONS_H
#define PATHS_FUNCTIONS_H

#include <string>

class PrefPathFinder;

namespace pathStr{

std::string getPrefPath(const PrefPathFinder& prefPath, const std::string& fileName);

}

#endif //PATHS_FUNCTIONS_H