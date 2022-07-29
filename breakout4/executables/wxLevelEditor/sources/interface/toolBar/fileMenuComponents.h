#ifndef TOOL_BAR_FILE_MENU_COMPONENTS_H
#define TOOL_BAR_FILE_MENU_COMPONENTS_H

#include "wx/menuitem.h"
#include "wx/menu.h"
#include <vector>

constexpr int OPEN_FILE = 201;
constexpr int SAVE_FILE = 202;

struct FileMenuComponents
{
	wxMenu *file;
	std::vector< wxMenuItem* > fileComponents;
	
	FileMenuComponents();
	void appendMenuItems();
};

#endif //TOOL_BAR_FILE_MENU_COMPONENTS_H