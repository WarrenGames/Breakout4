#include "prefPath/prefPathFinder.h"
#include "logging/logFile.h"
#include "SDL_filesystem.h"
#include "SDL_error.h"
#include <algorithm>

PrefPathFinder::PrefPathFinder(const std::string& organization, const std::string& appName, int squareSize):
	isPathFound{false}
{
	//'squareSize' parameter is the logical square size of a block of texture (for tile mapping).
	
	std::string finalAppName{appName + " sqr" + std::to_string(squareSize)};
	
	initialize(organization, finalAppName);
}

PrefPathFinder::PrefPathFinder(const std::string& organization, const std::string& appName):
	isPathFound{false}
{
	initialize(organization, appName);
}

PrefPathFinder::operator bool() const
{
	return isPathFound;
}

bool PrefPathFinder::isAValidPathFound() const
{
	return isPathFound;
}

std::string PrefPathFinder::getPath() const 
{
	return pathString.string();
}

const fs::path& PrefPathFinder::getFsPath() const
{
	return pathString;
}

const std::string& PrefPathFinder::getError() const
{
	return errorString;
}

void PrefPathFinder::outputErrorMessageIfAny(LogFile& log) const
{
	log.wrPrefixAndSimpleMessage("couldn't open a write access directory: " + errorString );
}

void PrefPathFinder::initialize(const std::string& organization, const std::string& finalAppName)
{
	char *pref_path = SDL_GetPrefPath(organization.c_str(), finalAppName.c_str());
	
	if( pref_path )
	{
		pathString = pref_path;
		isPathFound = true;
		SDL_free(pref_path);
	}
	else{
		isPathFound = false;
		errorString = SDL_GetError();
	}
}