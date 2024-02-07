#ifndef GAME_CONTEXTS_ONE_PLAYER_GAME_DEMO_LOADING_CONTEXT_H
#define GAME_CONTEXTS_ONE_PLAYER_GAME_DEMO_LOADING_CONTEXT_H

struct Essentials;
struct PlayerData;
namespace demos{ struct MainPackage; }
class TextButton;

namespace demosLoading{
	struct Interface;

	void mainContext(Essentials& essentials);

	void drawEverything(Essentials& essentials, const demosLoading::Interface& interface);
	
	void runDemoFile(Essentials& essentials, demosLoading::Interface& interface);
	
	void runLevelWithLoadedDemoData(Essentials& essentials, PlayerData& playerData, demos::MainPackage& demosMainPackage);
	
	void quitDemoMenu(Essentials& essentials, bool& quitMenu, const TextButton& quitButton);

}

#endif //GAME_CONTEXTS_ONE_PLAYER_GAME_DEMO_LOADING_CONTEXT_H