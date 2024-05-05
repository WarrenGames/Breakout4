#ifndef ONEPLGAME_SKILL_LEVEL_CHOICE_CONTEXT_H
#define ONEPLGAME_SKILL_LEVEL_CHOICE_CONTEXT_H

struct Essentials;

namespace onePlGame{
	namespace skillChoice{
		struct Interface;
		
		void context(Essentials& essentials, unsigned& chosenSkillLevel, bool& quitWholeMenus);
		
		void mainLoop(Essentials& essentials, onePlGame::skillChoice::Interface& interface, unsigned& chosenSkillLevel, bool& quitChoice, bool& quitWholeMenus);
		
		void redirectUser(Essentials& essentials, const onePlGame::skillChoice::Interface& interface, unsigned& chosenSkillLevel, bool& quitChoice, bool& quitWholeMenus);
		
		void checkSkillButtons(Essentials& essentials, const onePlGame::skillChoice::Interface& interface, unsigned& chosenSkillLevel, bool& quitChoice);
		
		void quitContext(Essentials& essentials, bool& quitChoice, bool& quitWholeMenus);
		
		void checkGoBackButton(const onePlGame::skillChoice::Interface& interface, bool& quitChoice, bool& quitWholeMenus);
		
		void drawEverything(Essentials& essentials, onePlGame::skillChoice::Interface& interface, bool& quitChoice);
		
	}
}

#endif //ONEPLGAME_SKILL_LEVEL_CHOICE_CONTEXT_H