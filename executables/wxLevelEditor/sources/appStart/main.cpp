#include "appStart/main.h"
#include "interface/mainLayout/mainFrame.h"
#include "logging/logFile.h"
#include "prefPath/wxPrefPath.h"
#include "consts/constexprScreen.h"
#include "consts/pathsConsts.h"
#include <fstream>
#include <iostream>

IMPLEMENT_APP(MyApp)

constexpr char ErrorFileName[] = "wxLevelEditorErrors.txt";

bool MyApp::OnInit()
{
	wxInitAllImageHandlers();
	
	const wxPrefPathFinder prefPath{Organization, GameTitle, SQR_SIZE};
	
	if( prefPath )
	{
		if( LogFile errorLog{ prefPath.getPath().ToStdString(), ErrorFileName, "Error: " } )
		{
			MainFrame *mainFrame = new MainFrame{errorLog};
			
			mainFrame->Centre();
			mainFrame->Show(true);
		}
		else{
			std::cout << "Error: couldn't open '" << ErrorFileName << "' in '" << prefPath.getPath() << "' path to log errors.\n";
		}
	}
	else{
		std::cout << "Error: couldn' t initialize pref path finder.\n";
	}
	return true;
}