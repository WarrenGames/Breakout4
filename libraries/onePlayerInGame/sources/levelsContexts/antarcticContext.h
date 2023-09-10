#ifndef ONE_PLAYER_ANTARCTIC_LEVEL_CONTEXT_H
#define ONE_PLAYER_ANTARCTIC_LEVEL_CONTEXT_H

struct LevelComponents;
struct PlayerData;
struct Essentials;
class LevelInputs;
struct AntarcticPackage;
namespace demos{ struct MainPackage; }

namespace antarcticLevel{
	void start(Essentials& essentials, PlayerData& playerData, bool& quitMainMenu);
	
	void startWithDemoRecording(Essentials& essentials, PlayerData& playerData, demos::MainPackage& demosMainPackage, bool& quitMainMenu);
	
	void startWithDemoRunning(Essentials& essentials, PlayerData& playerData, demos::MainPackage& demosMainPackage, bool& quitMainMenu);
	
	void playGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, PlayerData& playerData, AntarcticPackage& antarcticPackage, bool& quitMainMenu);
	
	void drawGame(Essentials& essentials, LevelComponents& levelComponents, AntarcticPackage& antarcticPackage);
}

#endif //ONE_PLAYER_ANTARCTIC_LEVEL_CONTEXT_H