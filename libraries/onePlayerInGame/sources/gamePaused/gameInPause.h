#ifndef ONE_PLAYER_GAME_IN_PAUSE_H
#define ONE_PLAYER_GAME_IN_PAUSE_H

struct Essentials;
struct LevelComponents;
struct PlayerData;
class PausedGameGUI;
class LevelInputs;
struct AntarcticPackage;
namespace onePlGame{ class HellPackage; }

namespace pausedGame{

void pauseTheGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, const PlayerData& playerData, bool& quitMainMenu, bool& quitGame);

void pauseTheAntarcticGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, const PlayerData& playerData, AntarcticPackage& antarcticPackage, bool& quitMainMenu, bool& quitGame);

void pauseTheHellGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, const PlayerData& playerData, onePlGame::HellPackage& hellPackage, bool& quitMainMenu, bool& quitGame);

void quitGame(const PausedGameGUI& pausedGameGUI, bool& quitMainMenu, bool& quitGame, bool& quiPause);

void drawPauseGUI(Essentials& essentials, LevelComponents& levelComponents);

void goBackToTheGame(Essentials& essentials, bool& quitPause);

void doPauseThings(LevelComponents& levelComponents, LevelInputs& levelInputs);

void endPause(LevelComponents& levelComponents);

bool isNotInRecordOrPlayDemoMode(const PlayerData& playerData);

}

#endif //ONE_PLAYER_GAME_IN_PAUSE_H