#ifndef PREF_PATH_FINDER_H
#define PREF_PATH_FINDER_H

#include "fileSystem/fileSystem.h"
#include <string>

class LogFile;

class PrefPathFinder
{
private:
	bool isPathFound;
	fs::path pathString;
	std::string	errorString;
	
public:
	//'squareSize' parameter is the logical square size of a block of texture (for tile mapping).
	explicit PrefPathFinder(const std::string& organization, const std::string& appName, int squareSize);
	explicit PrefPathFinder(const std::string& organization, const std::string& appName);
	~PrefPathFinder() = default;
	PrefPathFinder( const PrefPathFinder& ) = delete;
	PrefPathFinder& operator= (const PrefPathFinder& ) = delete;
	PrefPathFinder( PrefPathFinder&& ) = default;
	PrefPathFinder& operator= ( PrefPathFinder&& ) = default;
	
	operator bool() const;
	bool isAValidPathFound() const;
	std::string getPath() const;
	const fs::path& getFsPath() const;
	const std::string& getError() const;
	void outputErrorMessageIfAny(LogFile& log) const;
	
	void initialize(const std::string& Organization, const std::string& finalAppName);
};

#endif //PREF_PATH_FINDER_H