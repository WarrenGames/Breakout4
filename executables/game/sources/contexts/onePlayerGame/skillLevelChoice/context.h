#ifndef ONEPLGAME_SKILL_LEVEL_CHOICE_CONTEXT_H
#define ONEPLGAME_SKILL_LEVEL_CHOICE_CONTEXT_H

struct Essentials;

namespace onePlGame{
	namespace skillChoice{
		struct Interface;
		
		void context(Essentials& essentials);
		
		void mainLoop(Essentials& essentials, onePlGame::skillChoice::Interface& interface, bool& quitChoice);
		
		void redirectUser(Essentials& essentials, const onePlGame::skillChoice::Interface& interface, bool& quitChoice);
		
		void checkSkillButtons(Essentials& essentials, const onePlGame::skillChoice::Interface& interface, bool& quitChoice);
		
		void quitContext(Essentials& essentials, bool& quitChoice);
		
		void checkGoBackButton(const onePlGame::skillChoice::Interface& interface, bool& quitChoice);
		
		void drawEverything(Essentials& essentials, onePlGame::skillChoice::Interface& interface, bool& quitChoice);
		
	}
}

#endif //ONEPLGAME_SKILL_LEVEL_CHOICE_CONTEXT_H