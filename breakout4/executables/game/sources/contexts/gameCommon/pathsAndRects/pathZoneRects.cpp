#include "contexts/gameCommon/pathsAndRects/pathZoneRects.h"
#include "logging/logsStruct.h"
#include "consts/constexprScreen.h"
#include <sstream>

ZonesRectsLoader::ZonesRectsLoader(AppLogFiles& logs, const fs::path& rectsFilePath):
	isLoadingPerfect{ true }
{
	openFile(logs, rectsFilePath);
}

bool ZonesRectsLoader::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

std::vector< SDL_Rect >::const_iterator ZonesRectsLoader::cbegin() const
{
	return rects.cbegin();
}

std::vector< SDL_Rect >::const_iterator ZonesRectsLoader::cend() const
{
	return rects.cend();
}

void ZonesRectsLoader::openFile(AppLogFiles& logs, const fs::path& rectsFilePath)
{
	if( std::ifstream rectsFile{ rectsFilePath } )
	{
		std::size_t fileLineNumber{1};
		readSquareSizeRelativeRectsValues(logs, rectsFile, rectsFilePath, fileLineNumber);
	}
	else{
		logs.error.wrFileOpeningError(rectsFilePath.string(), "load path nodes");
		isLoadingPerfect = false;
	}
}

/*
void ZonesRectsLoader::getItemsNumberOnFirstLine(AppLogFiles& logs, std::ifstream& nodesFile, const fs::path& nodesFilePath, std::size_t& fileLineNumber)
{
	std::string fileLine;
	if( std::getline( nodesFile, fileLine ) )
	{
		std::size_t size{0};
		std::istringstream lineStream{ fileLine };
		if( lineStream >> size )
		{
			logs.warning << "Size of vector nodes read with success, its value is " << size << " .\n";
			rects.resize( size );
		}
		else{
			logs.error << "Error: first line read, but streaming that line to an 'std::size_t' value failed.\n";
		}
		fileLineNumber++;
	}
	else{
		logs.error << "Error: couldn't read first line of '" << nodesFilePath.string() << "' file in order to set nodes vector size.\n";
	}
}
*/

void ZonesRectsLoader::readSquareSizeRelativeRectsValues(AppLogFiles& logs, std::ifstream& rectsFile, const fs::path& rectsFilePath, std::size_t& fileLineNumber)
{
	std::string fileLine;
	SDL_Rect readRect;
	while( std::getline( rectsFile, fileLine ) )
	{
		std::istringstream lineStream{ fileLine };
		if( lineStream >> readRect.x >> readRect.y >> readRect.w >> readRect.h )
		{
			readRect.x *= SQR_SIZE;
			readRect.y *= SQR_SIZE;
			readRect.w *= SQR_SIZE;
			readRect.h *= SQR_SIZE;
			rects.emplace_back( readRect );
		}
		else{
			logs.error << "Error: the line number " << fileLineNumber << " of '" << rectsFilePath.string() << "' file was read but streaming data failed.\n";
		}
		fileLineNumber++;
	}
}