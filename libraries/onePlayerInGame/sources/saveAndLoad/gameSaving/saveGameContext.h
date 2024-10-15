#ifndef GAME_SAVING_CONTEXT_H
#define GAME_SAVING_CONTEXT_H

struct Essentials;
struct PlayerData;
class SlotsUserInterface;
struct TextureCombo;

namespace saveGame{
	void mainContext(Essentials& essentials, const PlayerData& playerData);
	
	void mainLoop(Essentials& essentials, const PlayerData& playerData, SlotsUserInterface& slotsGui, const TextureCombo& screenBackground, bool& quitSaveMenu);
	
	void saveASlot(Essentials& essentials, const PlayerData& playerData, SlotsUserInterface& slotsGui);
	
	void drawEverything(Essentials& essentials, const SlotsUserInterface& slotsGui, const TextureCombo& screenBackground);
	
	void quitContext(Essentials& essentials, const SlotsUserInterface& slotsGui, bool& quitSaveMenu);
}

#endif //GAME_SAVING_CONTEXT_H