#ifndef MAIN_FRAME_INTERFACE_H
#define MAIN_FRAME_INTERFACE_H

#include "interface/toolBar/menusBar.h"
#include "interface/currentGrid/onePlayerGrid/gridPanel.h"
#include "interface/currentGrid/onePlayerGrid/bricksTextures.h"
#include "interface/selectedBrick/selectedBrickPanel.h"
#include "interface/toolBar/toolbarIcons.h"
#include "wx/frame.h"
#include "wx/panel.h"
#include "wx/notebook.h"
#include "wx/sizer.h"
#include "wx/textctrl.h"

class SelectedBrickPanel;
class LogFile;

class MainFrame : public wxFrame
{
private:
	wxTextCtrl *logWindow;
	MenusBar menusBar;
	ToolbarIcons toolBarIcons;
	wxNotebook *notebook;
	OnePBricksTextures onePTextures;
	SelectedBrickPanel *brickChoicePanel;
	OnePlayerGridPanel *onePGrid;
	wxBoxSizer *hboxSizer;
	wxBoxSizer *vboxSizer;
	wxBoxSizer *lastVBoxSizer;

public:
	explicit MainFrame(LogFile& logFile);
	~MainFrame() = default;
	MainFrame( const MainFrame& ) = delete;
	MainFrame& operator= ( const MainFrame& ) = delete;
	
private:
	void loadGridFromFile(wxCommandEvent& event);
	void saveCurrentOnePlayerGrid(wxCommandEvent& event); 
	
	void bindBrickChoiceMenus();
	void bindTenPointsBricks();
	
	void logOnePBricksTextures();
};

#endif //MAIN_FRAME_INTERFACE_H