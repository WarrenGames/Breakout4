#include "interface/toolBar/menusBar.h"
#include "interface/toolBar/toolsMenusBar.h"

MenusBar::MenusBar():
	menusBar{ new wxMenuBar },
	toolsMenusBar{ }
{
	menusBar->Append( fileMenu.file, wxT("&File") );
	menusBar->Append( toolsMenusBar.tools, wxT("&Tools") );
	
}