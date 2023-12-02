#ifndef INTERFACE_TOOLS_MENUS_BAR_H
#define INTERFACE_TOOLS_MENUS_BAR_H

#include "interface/toolBar/brickChoiceMenusBar.h"

struct ToolsMenusBar
{
	wxMenu *tools;
	wxMenu *onePlayer;
	OneP_BrickChoiceMenusBar brickChoice;
	
	ToolsMenusBar();
	~ToolsMenusBar() = default;
	ToolsMenusBar( const ToolsMenusBar& ) = delete;
	ToolsMenusBar& operator= ( const ToolsMenusBar& ) = delete;
	ToolsMenusBar( ToolsMenusBar&& ) = default;
	ToolsMenusBar& operator= ( ToolsMenusBar&& ) = default;
};

#endif //INTERFACE_TOOLS_MENUS_BAR_H