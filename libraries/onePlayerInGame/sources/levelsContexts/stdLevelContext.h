#ifndef ONE_PLAYER_STD_LEVEL_CONTEXT_H
#define ONE_PLAYER_STD_LEVEL_CONTEXT_H

struct LevelComponents;
struct PlayerData;
struct Essentials;
class LevelInputs;
namespace demos{ struct MainPackage; }

namespace stdlevel{
	void start(Essentials& essentials, PlayerData& playerData, bool& quitMainMenu);
	
	void startWithDemoRecording(Essentials& essentials, PlayerData& playerData, demos::MainPackage& demosMainPackage, bool& quitMainMenu);
	
	void startWithDemoRunning(Essentials& essentials, PlayerData& playerData, demos::MainPackage& demosMainPackage, bool& quitMainMenu);
	
	void playGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, PlayerData& playerData, bool& quitMainMenu);
	
	void drawGame(Essentials& essentials, LevelComponents& levelComponents);
	
	void closeGameWindow(const LevelInputs& levelInputs, bool& quitMainMenu);
	
	void logLevelComponentsError(Essentials& essentials);
}

#endif //ONE_PLAYER_STD_LEVEL_CONTEXT_H