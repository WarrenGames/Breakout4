#include "contexts/gameCommon/movements/pathsLoader.h"
#include "logging/logsStruct.h"
#include <sstream>
#include <cassert>

PathsLoader::PathsLoader():
	isLoadingPerfect{true}
{
	
}

PathsLoader::PathsLoader(AppLogFiles& logs, const std::string& mainFilePath):
	isLoadingPerfect{true}
{
	populatePathVector(logs, mainFilePath);
}

bool PathsLoader::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

void PathsLoader::populatePathVector(AppLogFiles& logs, const std::string& mainFilePath)
{
	if( std::ifstream mainFile{ mainFilePath } )
	{
		std::string fileLine;
		while( std::getline( mainFile, fileLine ) )
		{
			addPathFromFile(logs, fileLine);
		}
	}
	else{
		logs.error << "Error: couldn't open '" << mainFilePath << "' main move file.\n";
		isLoadingPerfect = false;
	}
}

void PathsLoader::addPathFromFile(AppLogFiles& logs, const std::string& pathFile)
{
	if( std::ifstream file{pathFile} )
	{
		paths.emplace_back( PathData{} );
		std::string fileLine;
		PathSegment segment;
		unsigned waitingTime{0};
		while( std::getline( file, fileLine ) )
		{
			std::istringstream lineStream{fileLine};
			if( lineStream >> segment.vector.x >> segment.vector.y >> segment.speed >> waitingTime )
			{
				segment.waitingTime = std::chrono::milliseconds{waitingTime};
				paths.back().addPath( segment );
			}
			else{
				logs.error << "Error: couldn't read line of '" << pathFile << "' move file.\n";
				isLoadingPerfect = false;
			}
		}
	}
	else{
		logs.error << "Error: couldn't open '" << pathFile << "' move file.\n";
		isLoadingPerfect = false;
	}
}

std::size_t PathsLoader::size() const
{
	return paths.size();
}

std::size_t PathsLoader::getSegmentsNumber(std::size_t pathNumber) const
{
	assert( pathNumber < paths.size() );
	return paths[pathNumber].size();
}

const PathData& PathsLoader::getPath(std::size_t pathNumber) const
{
	assert( pathNumber < paths.size() );
	return paths[pathNumber];
}

const PathSegment& PathsLoader::getSegment(std::size_t pathNumber, std::size_t segmentNumber) const
{
	assert( pathNumber < paths.size() );
	assert( segmentNumber < paths[pathNumber].size() );
	return paths[pathNumber].getSegment(segmentNumber);
}