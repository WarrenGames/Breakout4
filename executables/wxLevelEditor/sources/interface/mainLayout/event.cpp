#include "interface/mainLayout/event.h"
#include <wx/utils.h> 

InterfaceEvents::InterfaceEvents():
	mouseState{ wxGetMouseState() }
{
	
}

void InterfaceEvents::updateMouseEvents()
{
	mouseState = wxGetMouseState();
}