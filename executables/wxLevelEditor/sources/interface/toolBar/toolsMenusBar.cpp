#include "interface/toolBar/toolsMenusBar.h"

ToolsMenusBar::ToolsMenusBar():
	tools{ new wxMenu{} },
	onePlayer{ new wxMenu{} },
	brickChoice{}
{
	onePlayer->AppendSubMenu(brickChoice.brickChoice, "Brick choice");
	tools->AppendSubMenu(onePlayer, wxT("One player menu") );
}