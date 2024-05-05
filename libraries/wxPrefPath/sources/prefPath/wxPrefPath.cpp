#include "prefPath/wxPrefPath.h"
#include "SDL_filesystem.h"
#include "SDL_error.h"

wxPrefPathFinder::wxPrefPathFinder(const wxString& organization, const wxString& appName, int squareSize):
	isPathFound{ false }
{
	wxString finalAppName{ appName + " sqr"};
	finalAppName << static_cast<unsigned>( squareSize );
	
	initialize(organization, finalAppName);
}

wxPrefPathFinder::wxPrefPathFinder(const wxString& organization, const wxString& appName):
	isPathFound{ false }
{
	initialize( organization, appName);		
}

wxPrefPathFinder::operator bool() const
{
	return isPathFound;
}

const wxString& wxPrefPathFinder::getPath() const
{
	return prefPath;
}

const fs::path& wxPrefPathFinder::getFsPath() const
{
	return fsPrefPath;
}

const wxString& wxPrefPathFinder::getError() const
{
	return errorString;
}

void wxPrefPathFinder::initialize(const wxString& organization, const wxString& finalAppName)
{
	char *pref_path = SDL_GetPrefPath(organization.c_str(), finalAppName.c_str());
	
	if( pref_path )
	{
		prefPath = pref_path;
		fsPrefPath = pref_path;
		isPathFound = true;
		SDL_free( pref_path );
		errorString = "Everything went fine.";
	}
	else{
		isPathFound = false;
		errorString = SDL_GetError();
	}
}