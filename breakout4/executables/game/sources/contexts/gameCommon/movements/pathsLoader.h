#ifndef FIRE_BALL_PATH_LOADER_H
#define FIRE_BALL_PATH_LOADER_H

#include "contexts/gameCommon/movements/movePathData.h"
#include <string>

struct AppLogFiles;

class PathsLoader
{
private:
	std::vector< PathData > paths;
	bool isLoadingPerfect;

public:
	explicit PathsLoader();
	explicit PathsLoader(AppLogFiles& logs, const std::string& mainFilePath);
	~PathsLoader() = default;
	PathsLoader( const PathsLoader& ) = delete;
	PathsLoader& operator= ( const PathsLoader& ) = delete;
	PathsLoader( PathsLoader&& ) = default;
	PathsLoader& operator= ( PathsLoader&& ) = default;
	
	bool wasLoadingPerfect() const;
	
	void populatePathVector(AppLogFiles& logs, const std::string& mainFilePath);
	void addPathFromFile(AppLogFiles& logs, const std::string& pathFile);
	std::size_t size() const;
	std::size_t getSegmentsNumber(std::size_t pathNumber) const;
	const PathData& getPath(std::size_t pathNumber) const;
	const PathSegment& getSegment(std::size_t pathNumber, std::size_t segmentNumber) const;
};

#endif //FIRE_BALL_PATH_LOADER_H