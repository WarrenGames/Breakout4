#include "appStart/main.h"
#include "interface/mainLayout/mainFrame.h"
#include "logging/logFile.h"
#include "prefPath/prefPathFinder.h"
#include "consts/constexprScreen.h"
#include "consts/pathsConsts.h"
#include <fstream>
#include <iostream>

IMPLEMENT_APP(MyApp)

constexpr char ERROR_FILE_NAME[] = "wxLevelEditorErrors.txt";

bool MyApp::OnInit()
{
	wxInitAllImageHandlers();
	
	const PrefPathFinder prefPath{ORGANIZATION, GAME_TITLE, SQR_SIZE};
	
	if( prefPath )
	{
		if( LogFile errorLog{ prefPath.getPath(), ERROR_FILE_NAME, "Error: " } )
		{
			MainFrame *mainFrame = new MainFrame{errorLog};
			
			mainFrame->Centre();
			mainFrame->Show(true);
		}
		else{
			std::cout << "Error: couldn't open '" << ERROR_FILE_NAME << "' in '" << prefPath.getPath() << "' path to log errors.\n";
		}
	}
	else{
		std::cout << "Error: couldn' t initialize pref path finder.\n";
	}
	return true;
}