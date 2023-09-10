#ifndef APP_TOOLBAR_ICONS_H
#define APP_TOOLBAR_ICONS_H

#include <wx/bitmap.h>
#include <wx/toolbar.h>
#include <vector>

class wxFrame;

struct ToolbarIcons
{
	wxBitmap shiftUpIcon;
	wxBitmap shiftDownIcon;
	std::vector< wxBitmap > bricksSelectorIcons;
	
	wxToolBar *toolbar;
	
	explicit ToolbarIcons(wxFrame *frame);
	~ToolbarIcons() = default;
	ToolbarIcons( const ToolbarIcons& ) = delete;
	ToolbarIcons& operator= ( const ToolbarIcons& ) = delete;
	ToolbarIcons( ToolbarIcons&& ) = default;
	ToolbarIcons& operator= ( ToolbarIcons&& ) = default;
	
};

#endif //APP_TOOLBAR_ICONS_H