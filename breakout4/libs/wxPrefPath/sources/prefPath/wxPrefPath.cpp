#include "prefPath/wxPrefPath.h"
#include "SDL.h"

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
		isPathFound = true;
		SDL_free( pref_path );
		//prefPath.Replace("\\", "/", true);
	}
	else{
		isPathFound = false;
		errorString = SDL_GetError();
	}
}