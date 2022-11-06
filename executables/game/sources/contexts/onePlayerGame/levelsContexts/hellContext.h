#ifndef ONE_PLAYER_HELL_LEVEL_CONTEXT_H
#define ONE_PLAYER_HELL_LEVEL_CONTEXT_H

struct LevelComponents;
struct PlayerData;
struct Essentials;
class LevelInputs;
namespace onePlGame{ class HellPackage; }

namespace hellLevel{
	void start(Essentials& essentials, PlayerData& playerData, bool& quitMainMenu);
	
	void playGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, PlayerData& playerData, onePlGame::HellPackage& hellPackage, bool& quitMainMenu);
	
	void drawGame(Essentials& essentials, LevelComponents& levelComponents, onePlGame::HellPackage& hellPackage);
}

#endif //ONE_PLAYER_HELL_LEVEL_CONTEXT_H