#ifndef APP_MAIN_FRAME_H
#define APP_MAIN_FRAME_H

#include "interface/menuBar.h"
#include "interface/headersInterface.h"
#include "interface/gameObjectsInterface.h"
#include "interface/bagBonusesInterface.h"
#include "data/gameSlots.h"
#include "texts/textLoader.h"
#include "wx/frame.h"
#include <wx/sizer.h>
#include <wx/notebook.h>

struct AppStartData;
class wxPrefPathFinder;
struct AppLogFiles;

class MyFrame : public wxFrame
{
private:
	MenuBar menuBar;
	wxNotebook* notebook;
	wxTextCtrl* logWindow;
	wxBoxSizer* vBoxSizer;
	HeaderInterface headerInterface;
	GameObjectsInterface gameObjectsInterface;
	BagBonusesInterface bagBonusesInterface;
	GameSaveSlots savesSlots;
	const wxPrefPathFinder& prefPath;
	AppLogFiles& logs;
	const TextsBlocks headersTexts;
	const wxString gameSavePath;

public:
	explicit MyFrame(AppStartData& appStartData);
	~MyFrame() = default;
	MyFrame( const MyFrame& ) = delete;
	MyFrame& operator= ( const MyFrame& ) = delete;
	MyFrame( MyFrame&& ) = default;
	MyFrame& operator= ( MyFrame&& ) = default;

private:
	void bindMenuBar();
	void bindSkillLevelMenu(wxCommandEvent& event);
	void bindCampaignType(wxCommandEvent& event);
	void bindRacketSize(wxCommandEvent& event);
	void bindRimSize(wxCommandEvent& event);
	void bindCampaignHeaderMenu(wxCommandEvent& event);
	void bindScoreHeaderMenu(wxCommandEvent& event);
	
	void setWidgetsWithLoadedSlot();//After loading data from file on disk from 'file dialog'
	void checkTextCtrlValues() const;//To check if current wxWidgets (wxTextCtrl) can be saved to file on disk
	void runAssignations(GameSlotData& slot) const;//Run in 'checkTextCtrlValues()' function
	void saveToFileDialog(wxCommandEvent& event);//Open a window to save current slot to file on disk
	void loadFromFileDialog(wxCommandEvent& event);//Open a window from which a file can be selected to write slot data
	void setCurrentValuesToSlot();
	void logPrefPathStatus();
	void atStartLogging(const AppStartData& appStartData);
};

#endif //APP_MAIN_FRAME_H