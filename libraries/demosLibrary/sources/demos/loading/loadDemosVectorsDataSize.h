#ifndef DEMOS_LIB_LOAD_DEMOS_VECTORS_DATA_SIZE_H
#define DEMOS_LIB_LOAD_DEMOS_VECTORS_DATA_SIZE_H

#include <string>

struct AppLogFiles;
class PrefPathFinder;

namespace demos{
	std::size_t getVectorsDataSize(AppLogFiles& logs, const PrefPathFinder& prefPath, const std::string& fileName);
}

#endif //DEMOS_LIB_LOAD_DEMOS_VECTORS_DATA_SIZE_H