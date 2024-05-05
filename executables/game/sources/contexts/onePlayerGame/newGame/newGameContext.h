#ifndef ONE_PLAYER_NEW_GAME_CONTEXT_H
#define ONE_PLAYER_NEW_GAME_CONTEXT_H

struct Essentials;

namespace onePlGame{
	namespace newGame{
		struct Interface;
		
		void context(Essentials& essentials, unsigned& chosenMenuItem, bool& quitWholeMenus);
		
		void mainLoop(Essentials& essentials, onePlGame::newGame::Interface& interface, unsigned& chosenMenuItem, bool& quitNewGameMenu, bool& quitWholeMenus);
		
		void update(Essentials& essentials, onePlGame::newGame::Interface& interface, unsigned& chosenMenuItem, bool& quitNewGameMenu, bool& quitWholeMenus);
		
		void redirectUser(Essentials& essentials, const onePlGame::newGame::Interface& interface, unsigned& chosenMenuItem, bool& quitNewGameMenu);
		
		void quitContext(Essentials& essentials, bool& quitNewGameMenu, bool& quitWholeMenus);
		
		void startNewGame(Essentials& essentials, const onePlGame::newGame::Interface& interface, unsigned& chosenMenuItem, bool& quitNewGameMenu);
		
		void loadSavedGame(Essentials& essentials, const onePlGame::newGame::Interface& interface, unsigned& chosenMenuItem, bool& quitNewGameMenu);
		
		void seeDoneScores(Essentials& essentials, const onePlGame::newGame::Interface& interface, unsigned& chosenMenuItem, bool& quitNewGameMenu);
		
		void recordDemo(Essentials& essentials, const onePlGame::newGame::Interface& interface, unsigned& chosenMenuItem, bool& quitNewGameMenu);
		
		void playDemo(Essentials& essentials, const onePlGame::newGame::Interface& interface, unsigned& chosenMenuItem, bool& quitNewGameMenu);
		
		void goBack(Essentials& essentials, const onePlGame::newGame::Interface& interface, unsigned& chosenMenuItem, bool& quitNewGameMenu);
		
		void drawEverything(Essentials& essentials, onePlGame::newGame::Interface& interface, bool& quitNewGameMenu);
	}
}


#endif //ONE_PLAYER_NEW_GAME_CONTEXT_H