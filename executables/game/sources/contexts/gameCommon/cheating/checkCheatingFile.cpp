#include "contexts/gameCommon/cheating/checkCheatingFile.h"
#include "prefPath/prefPathFinder.h"
#include <fstream>

CheatingFile::CheatingFile(const PrefPathFinder& prefPath, const std::string& subPath):
	isCheatActive{false}
{
	readFile(prefPath.getPath() + subPath);
}

bool CheatingFile::wasFileWithDataFound() const
{
	return isCheatActive;
}

void CheatingFile::readFile(const std::string& fileFullPath)
{
	if( std::ifstream cheatingFile{ fileFullPath } )
	{
		unsigned data{0};
		if( cheatingFile >> data )
		{
			if( data == 1 )
				isCheatActive = true;
		}
	}
}