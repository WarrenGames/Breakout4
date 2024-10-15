#ifndef COMMON_FILES_MINI_SCREEN_GUI_CONSTS_H
#define COMMON_FILES_MINI_SCREEN_GUI_CONSTS_H

#include <cstdlib>

namespace miniScreenTexts{
	enum : std::size_t{
		F1_FullScreen,			// = 0
		F5_WindowedMode,		// = 1
		WarningBetaVersion,		// = 2
		PressEscapeToGoBack,	// = 3
		ToThePreviousMenu,		// = 4
		Max						// = 5
	};
}

#endif //COMMON_FILES_MINI_SCREEN_GUI_CONSTS_H