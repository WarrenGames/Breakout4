#ifndef GAME_LOADING_CONTEXT_H
#define GAME_LOADING_CONTEXT_H

struct Essentials;
struct PlayerData;
class SlotsUserInterface;

namespace loadGame{
	void mainContext(Essentials& essentials, PlayerData& playerData);
	
	void mainLoop(Essentials& essentials, PlayerData& playerData, SlotsUserInterface& slotsGui, bool& quitLoadGameMenu);
	
	void loadASlot(Essentials& essentials, PlayerData& playerData, const SlotsUserInterface& slotsGui, bool& quitLoadGameMenu);
	
	void drawEverything(Essentials& essentials, const SlotsUserInterface& slotsGui, bool& quitLoadGameMenu);
	
	void quitContext(Essentials& essentials, const SlotsUserInterface& slotsGui, bool& quitSaveMenu);
}

#endif //GAME_LOADING_CONTEXT_H