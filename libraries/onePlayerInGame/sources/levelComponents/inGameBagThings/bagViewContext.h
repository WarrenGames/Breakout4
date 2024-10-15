#ifndef ONE_PLAYER_BAG_VIEW_CONTEXT_H
#define ONE_PLAYER_BAG_VIEW_CONTEXT_H

struct Essentials;
class LevelInputs;
struct LevelComponents;
struct PlayerData;
struct PlayerBag;
class AccurateTimeDelay;

namespace bagView{
	void startBagContext(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, PlayerData& playerData);
	
	void mainContext(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, PlayerData& playerData);
	
	void listenToPlayerInputs(LevelInputs& levelInputs, LevelComponents& levelComponents, PlayerData& playerData, PlayerBag& playerBag, AccurateTimeDelay& bonusSwitchingDelay);
	
	void selectNextBonus(LevelInputs& levelInputs, PlayerBag& playerBag, AccurateTimeDelay& bonusSwitchingDelay);
	
	void selectPreviousBonus(LevelInputs& levelInputs, PlayerBag& playerBag, AccurateTimeDelay& bonusSwitchingDelay);
	
	void quitContext(LevelInputs& levelInputs, bool& quitBagView);
	
	void useBonus(LevelInputs& levelInputs, LevelComponents& levelComponents, PlayerData& playerData, PlayerBag& playerBag);
	
	void drawEverything(Essentials& essentials, LevelComponents& levelComponents, const PlayerBag& playerBag);
	
	void drawSelectionRect(Essentials& essentials, const PlayerBag& playerBag);
}


#endif //ONE_PLAYER_BAG_VIEW_CONTEXT_H