#ifndef MAIN_LAYOUT_EVENT_H
#define MAIN_LAYOUT_EVENT_H

#include <wx/mousestate.h>

struct InterfaceEvents
{
	wxMouseState mouseState;
	
	explicit InterfaceEvents();
	~InterfaceEvents() = default;
	InterfaceEvents( const InterfaceEvents& ) = delete;
	InterfaceEvents& operator= ( const InterfaceEvents& ) = delete;
	
	void updateMouseEvents();
};

#endif //MAIN_LAYOUT_EVENT_H