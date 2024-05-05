#ifndef SHOP_RACE_MAIN_MENU_CONTEXT_H
#define SHOP_RACE_MAIN_MENU_CONTEXT_H

#include <string>

struct Essentials;
struct PlayerData;

namespace onePlGame{
	namespace raceMainMenu{
		struct Interface;
		
		void context(Essentials& essentials, unsigned skillLevel, unsigned raceType);
		
		void fromGameSaveContext(Essentials& essentials, PlayerData& playerData);
		
		void mainLoop(Essentials& essentials, onePlGame::raceMainMenu::Interface& interface, PlayerData& playerData, bool quitMainMenu);
		
		void drawEverything(Essentials& essentials, const onePlGame::raceMainMenu::Interface& interface, bool quitMainMenu);
		
		void redirectUser(Essentials& essentials, PlayerData& playerData, const onePlGame::raceMainMenu::Interface& interface, bool& quitMainMenu);
		
		void goToInputConfig(Essentials& essentials, const onePlGame::raceMainMenu::Interface& interface);
		
		void quitContext(Essentials& essentials, const onePlGame::raceMainMenu::Interface& interface, bool& quitMainMenu);
		
		void runNextLevel(Essentials& essentials, PlayerData& playerData, const onePlGame::raceMainMenu::Interface& interface, bool& quitMainMenu);
		
		void selectLevelToRun(Essentials& essentials, PlayerData& playerData, bool& quitMainMenu);
		
		void runSpecificLevel(Essentials& essentials, PlayerData& playerData, bool& quitMainMenu);
		
		void goToShop(Essentials& essentials, PlayerData& playerData, const onePlGame::raceMainMenu::Interface& interface);
		
		void seeNextLevel(Essentials& essentials, PlayerData& playerData, const onePlGame::raceMainMenu::Interface& interface);
		
		void goToSaveGameContext(Essentials& essentials, PlayerData& playerData, const onePlGame::raceMainMenu::Interface& interface);
		
		void displayCampaignEnd(Essentials& essentials, const PlayerData& playerData, bool& quitMainMenu);
	}
}

#endif //SHOP_RACE_MAIN_MENU_CONTEXT_H