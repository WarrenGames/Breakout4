#ifndef GENERIC_LIB_PATHS_CONCATENATE_H
#define GENERIC_LIB_PATHS_CONCATENATE_H

#include "fileSystem/fileSystem.h"

namespace path{

fs::path getConcatenatedPaths(const fs::path& path1, const fs::path& path2);

}

#endif //GENERIC_LIB_PATHS_CONCATENATE_H