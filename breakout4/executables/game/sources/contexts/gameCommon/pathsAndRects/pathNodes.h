#ifndef PATH_NODES_LOADER_H
#define PATH_NODES_LOADER_H

#include "customTypes/positionTypes.h"
#include "fileSystem/fileSystem.h"
#include <vector>
#include <iosfwd>

struct AppLogFiles;

class PathNodesLoader
{
private:
	std::vector< Offset > nodes;
	bool isLoadingPerfect;
	
public:
	explicit PathNodesLoader(AppLogFiles& logs, const fs::path& nodesFilePath);
	~PathNodesLoader() = default;
	PathNodesLoader( const PathNodesLoader& ) = delete;
	PathNodesLoader& operator= ( const PathNodesLoader& ) = delete;
	PathNodesLoader( PathNodesLoader&& ) = default;
	PathNodesLoader& operator= ( PathNodesLoader&& ) = default;
	
	bool wasLoadingPerfect() const;
	std::vector< Offset >::const_iterator cbegin() const;
	std::vector< Offset >::const_iterator cend() const;
	
private:
	void openFile(AppLogFiles& logs, const fs::path& nodesFilePath);
	void getItemsNumberOnFirstLine(AppLogFiles& logs, std::ifstream& nodesFile, const fs::path& nodesFilePath, std::size_t& fileLineNumber);
	void readSquareSizeRelativeNodesValues(AppLogFiles& logs, std::ifstream& nodesFile, const fs::path& nodesFilePath, std::size_t& fileLineNumber);
};

#endif //PATH_NODES_LOADER_H