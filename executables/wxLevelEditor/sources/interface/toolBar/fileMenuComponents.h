#ifndef TOOL_BAR_FILE_MENU_COMPONENTS_H
#define TOOL_BAR_FILE_MENU_COMPONENTS_H

#include "wx/menuitem.h"
#include "wx/menu.h"
#include <vector>

namespace fileHandling{
	constexpr int OpenFile = 201;
	constexpr int SaveFile = 202;
}

struct FileMenuComponents
{
	wxMenu *file;
	std::vector< wxMenuItem* > fileComponents;
	
	FileMenuComponents();
	void appendMenuItems();
};

#endif //TOOL_BAR_FILE_MENU_COMPONENTS_H