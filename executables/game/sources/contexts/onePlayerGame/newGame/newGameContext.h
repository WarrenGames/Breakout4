#ifndef ONE_PLAYER_NEW_GAME_CONTEXT_H
#define ONE_PLAYER_NEW_GAME_CONTEXT_H

struct Essentials;

namespace onePlGame{
	namespace newGame{
		struct Interface;
		
		void context(Essentials& essentials);
		
		void mainLoop(Essentials& essentials, onePlGame::newGame::Interface& interface, bool& quitNewGameMenu);
		
		void update(Essentials& essentials, onePlGame::newGame::Interface& interface, bool& quitNewGameMenu);
		
		void redirectUser(Essentials& essentials, const onePlGame::newGame::Interface& interface, bool& quitNewGameMenu);
		
		void quitContext(Essentials& essentials, bool& quitNewGameMenu);
		
		void startNewGame(Essentials& essentials, const onePlGame::newGame::Interface& interface, bool& quitNewGameMenu);
		
		void loadSavedGame(Essentials& essentials, const onePlGame::newGame::Interface& interface, bool& quitNewGameMenu);
		
		void seeDoneScores(Essentials& essentials, const onePlGame::newGame::Interface& interface, bool& quitNewGameMenu);
		
		void goBack(Essentials& essentials, const onePlGame::newGame::Interface& interface, bool& quitNewGameMenu);
		
		void drawEverything(Essentials& essentials, onePlGame::newGame::Interface& interface, bool& quitNewGameMenu);
	}
}


#endif //ONE_PLAYER_NEW_GAME_CONTEXT_H