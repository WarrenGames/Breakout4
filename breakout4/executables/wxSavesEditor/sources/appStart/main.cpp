#include "appStart/main.h"
#include "appStart/appStartData.h"
#include "interface/myFrame.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	AppStartData appStartData;
	
	if( appStartData )
	{
		MyFrame* myFrame{ new MyFrame{appStartData} };
	
		myFrame->Centre();
		myFrame->Show(true);
	}
	return true;
}