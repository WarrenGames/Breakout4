#ifndef WX_PREF_PATH_H
#define WX_PREF_PATH_H

#include "fileSystem/fileSystem.h"
#include <wx/string.h>

class wxPrefPathFinder
{
private:
	wxString prefPath;
	fs::path fsPrefPath;
	wxString errorString;
	bool isPathFound;

public:
	explicit wxPrefPathFinder(const wxString& organization, const wxString& appName, int squareSize);
	explicit wxPrefPathFinder(const wxString& organization, const wxString& appName);
	~wxPrefPathFinder() = default;
	wxPrefPathFinder( const wxPrefPathFinder& ) = delete;
	wxPrefPathFinder& operator= ( const wxPrefPathFinder& ) = delete;
	wxPrefPathFinder( wxPrefPathFinder&& ) = default;
	wxPrefPathFinder& operator= ( wxPrefPathFinder&& ) = default;
	
	operator bool() const;
	
	const wxString& getPath() const;
	const fs::path& getFsPath() const;
	const wxString& getError() const;
	void initialize(const wxString& organization, const wxString& finalAppName);
};

#endif //WX_PREF_PATH_H