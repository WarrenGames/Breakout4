#ifndef GAME_SAVING_CONTEXT_H
#define GAME_SAVING_CONTEXT_H

struct Essentials;
struct PlayerData;
class SlotsUserInterface;

namespace saveGame{
	void mainContext(Essentials& essentials, const PlayerData& playerData);
	
	void mainLoop(Essentials& essentials, const PlayerData& playerData, SlotsUserInterface& slotsGui, bool& quitSaveMenu);
	
	void saveASlot(Essentials& essentials, const PlayerData& playerData, SlotsUserInterface& slotsGui);
	
	void drawEverything(Essentials& essentials, const SlotsUserInterface& slotsGui);
	
	void quitContext(Essentials& essentials, const SlotsUserInterface& slotsGui, bool& quitSaveMenu);
}

#endif //GAME_SAVING_CONTEXT_H