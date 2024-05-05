#include "appStart/main.h"
#include "appStart/appStartData.h"
#include "interface/myFrame.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	if( AppStartData appStartData{} )
	{
		MyFrame* myFrame{ new MyFrame{appStartData} };
		
		myFrame->Centre();
		myFrame->Show(true);
	}
	return true;
}