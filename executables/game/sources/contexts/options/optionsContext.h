#ifndef OPTIONS_MENU_CONTEXT_H
#define OPTIONS_MENU_CONTEXT_H

struct Essentials;

namespace optionsMenu{
	class MainMenu;
	
	void mainInterface(Essentials& essentials);
	
	void redirectUser(Essentials& essentials, optionsMenu::MainMenu& menu);
	
	void goToLanguagesPanel(Essentials& essentials, optionsMenu::MainMenu& menu);
	
	void goToGraphicsPanel(Essentials& essentials, optionsMenu::MainMenu& menu);
	
	void goToSoundsPanel(Essentials& essentials, optionsMenu::MainMenu& menu);
	
	void goToMusicPanel(Essentials& essentials, optionsMenu::MainMenu& menu);
	
	void drawEverything(Essentials& essentials, const optionsMenu::MainMenu& menu);
	
	void exitMenu(Essentials& essentials, bool& quitMenu);
	
	void exitWithTextButton(const optionsMenu::MainMenu& menu, bool& quitMenu);
}

#endif //OPTIONS_MENU_CONTEXT_H