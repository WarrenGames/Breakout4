#ifndef INTERFACE_TOOLS_MENUS_BAR_H
#define INTERFACE_TOOLS_MENUS_BAR_H

#include "interface/toolBar/brickChoiceMenusBar.h"

struct ToolsMenusBar
{
	wxMenu *tools;
	wxMenu *onePlayer;
	OneP_BrickChoiceMenusBar brickChoice;
	
	ToolsMenusBar();
};

#endif //INTERFACE_TOOLS_MENUS_BAR_H