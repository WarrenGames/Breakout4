#include "contexts/gameCommon/pathsAndRects/pathNodes.h"
#include "logging/logsStruct.h"
#include "consts/constexprScreen.h"
#include <sstream>

PathNodesLoader::PathNodesLoader(AppLogFiles& logs, const fs::path& nodesFilePath):
	isLoadingPerfect{true}
{
	openFile(logs, nodesFilePath);
}

bool PathNodesLoader::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

std::vector< Offset >::const_iterator PathNodesLoader::cbegin() const
{
	return nodes.cbegin();
}

std::vector< Offset >::const_iterator PathNodesLoader::cend() const
{
	return nodes.cend();
}

void PathNodesLoader::openFile(AppLogFiles& logs, const fs::path& nodesFilePath)
{
	if( std::ifstream nodesFile{ nodesFilePath } )
	{
		std::size_t fileLineNumber{1};
		getItemsNumberOnFirstLine(logs, nodesFile, nodesFilePath, fileLineNumber);
		readSquareSizeRelativeNodesValues(logs, nodesFile, nodesFilePath, fileLineNumber);
	}
	else{
		logs.error.wrFileOpeningError(nodesFilePath.string(), "load path nodes");
		isLoadingPerfect = false;
	}
}

void PathNodesLoader::getItemsNumberOnFirstLine(AppLogFiles& logs, std::ifstream& nodesFile, const fs::path& nodesFilePath, std::size_t& fileLineNumber)
{
	std::string fileLine;
	if( std::getline( nodesFile, fileLine ) )
	{
		std::size_t size{0};
		std::istringstream lineStream{ fileLine };
		if( lineStream >> size )
		{
			logs.warning << "Size of vector nodes read with success, its value is " << size << " .\n";
			nodes.resize( size );
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

void PathNodesLoader::readSquareSizeRelativeNodesValues(AppLogFiles& logs, std::ifstream& nodesFile, const fs::path& nodesFilePath, std::size_t& fileLineNumber)
{
	std::string fileLine;
	std::size_t nodeNumber{0};
	AccurCoords coords;
	Offset finalCoords;
	while( std::getline( nodesFile, fileLine ) )
	{
		std::istringstream lineStream{ fileLine };
		if( lineStream >> nodeNumber >> coords.x >> coords.y )
		{
			if( nodeNumber < nodes.size() )
			{
				finalCoords.x = static_cast<int>( coords.x * SQR_SIZE );
				finalCoords.y = static_cast<int>( coords.y * SQR_SIZE );
				nodes[nodeNumber] = finalCoords;
			}
			else{
				logs.error << "Error: a node number is too high for nodes vector size at line " << fileLineNumber << " in '" << nodesFilePath.string() << "' file.\n";
			}
		}
		else{
			logs.error << "Error: the line number " << fileLineNumber << " of '" << nodesFilePath.string() << "' file was read but streaming data failed.\n";
		}
		fileLineNumber++;
	}
}