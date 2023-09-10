#include "fileSystem/pathsConcatenate.h"

fs::path path::getConcatenatedPaths(const fs::path& path1, const fs::path& path2)
{
	fs::path finalPath{ path1 };
	finalPath /= path2;
	return finalPath;
}