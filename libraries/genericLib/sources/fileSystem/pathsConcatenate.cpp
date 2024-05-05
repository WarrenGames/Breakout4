#include "fileSystem/pathsConcatenate.h"

fs::path path::getConcatenatedPaths(const fs::path& path1, const fs::path& path2)
{
	return path1 / path2;
}