#ifndef INTERFACE_MENUS_BAR_H
#define INTERFACE_MENUS_BAR_H

#include "interface/toolBar/fileMenuComponents.h"
#include "interface/toolBar/toolsMenusBar.h"
#include "wx/menu.h"

struct MenusBar
{
	wxMenuBar *menusBar;
	FileMenuComponents fileMenu;
	ToolsMenusBar toolsMenusBar;
	
	MenusBar();
	~MenusBar() = default;
	MenusBar( const MenusBar& ) = delete;
	MenusBar& operator= ( const MenusBar& ) = delete;
	MenusBar( MenusBar&& ) = default;
	MenusBar& operator= ( MenusBar&& ) = default;
};

#endif //INTERFACE_MENUS_BAR_H