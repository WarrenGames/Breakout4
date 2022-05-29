#ifndef OPTIONS_LANGUAGE_CONSTS_H
#define OPTIONS_LANGUAGE_CONSTS_H

namespace joyStrings{
	enum{	TITLE, 
			AXES_ENUM, 
			HATS_ENUM, 
			BUTTONS_ENUM, 
			NOJOY_PLUG, 
			BTNS_UNAVAIL, 
			AXES_UNAVAIL, 
			HATS_UNAVAIL, 
			AXES_THRES, 
			CALIBR_JOY, 
			PROMPT_PRESS_A, 
			PROMPT_JOY_BUTTON, 
			HAT_NUM, 
			AXIS_NUM, 
			BUTTON_NUM, 
			MAX};
}

namespace joyTexts{
	enum{	JOY_INTERFACE, 
			JOY_NAME, 
			JOY_BTN, 
			JOY_AXES, 
			JOY_HATS, 
			JOY_THRES, 
			JOY_CALIBR, 
			MAX };
	
	enum{	CALIBR_QUIT, 
			CALIBR_HELP_TUNE, 
			CALIBR_MAX };
}

namespace keybStrings{
	enum{	LEFT, 
			RIGHT, 
			UP, 
			DOWN, 
			SHOOT, 
			SELECT_WEAPON, 
			MEGABOMB, 
			PRESS_A, 
			NEW_KEY, 
			MAX };
}


namespace audioLang{

enum{	SOUND, 
		MUSIC, 
		ENABLED, 
		DISABLED, 
		CHANGE, 
		PLAY_SOUND, 
		PLAY_MUSIC, 
		MAX };

}

namespace langTexts{
	enum{ 	AVAILABLE_LANGS, 
			SELECTED_LANGS, 
			MAX };
}

#endif //OPTIONS_LANGUAGE_CONSTS_H