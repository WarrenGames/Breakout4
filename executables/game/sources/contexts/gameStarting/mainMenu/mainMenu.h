#ifndef MAIN_MENU_H
#define MAIN_MENU_H

struct Essentials;
namespace mainMenu{ struct Widgets; }
struct TextureCombo;
class AccurateTimeDelay;
class TextButton;

namespace mainMenu{
	
	void menu(Essentials& essentials);
	
	void mainLoop(Essentials& essentials, mainMenu::Widgets& buttons, bool& quitMenu, const TextureCombo& background);
	
	void drawEverything(Essentials& essentials, mainMenu::Widgets& buttons, bool& quitMenu, const TextureCombo& background);
	
	void quitMenu(Essentials& essentials, bool& quitMenu, const TextButton& quitButton);
	
	void runOnePlayerGame(Essentials& essentials, const TextButton& gameButton);
	
	void onePlayerGameSteps(Essentials& essentials);
	
	void onePlayerRedirect(Essentials& essentials, unsigned& chosenSkillLevel, unsigned& chosenMenuItem, bool& quitWholeMenus);
	
	void loadGame(Essentials& essentials);
	
	void runDuels(Essentials& essentials, const TextButton& duelsButton);
	
	void runCredits(Essentials& essentials, const TextButton& creditsButton);
	
	void runOptions(Essentials& essentials, const TextButton& optionsButton);
}

#endif //MAIN_MENU_H