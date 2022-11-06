#ifndef ONE_PLAYER_GAME_IN_PAUSE_H
#define ONE_PLAYER_GAME_IN_PAUSE_H

struct Essentials;
struct LevelComponents;
class PausedGameGUI;
class LevelInputs;
struct AntarcticPackage;
namespace onePlGame{ class HellPackage; }

namespace pausedGame{

void pauseTheGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, bool& quitMainMenu, bool& quitGame);

void pauseTheAntarcticGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, AntarcticPackage& antarcticPackage, bool& quitMainMenu, bool& quitGame);

void pauseTheHellGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, onePlGame::HellPackage& hellPackage, bool& quitMainMenu, bool& quitGame);

void quitGame(const PausedGameGUI& pausedGameGUI, bool& quitMainMenu, bool& quitGame, bool& quiPause);

void drawPauseGUI(Essentials& essentials, LevelComponents& levelComponents);

void goBackToTheGame(Essentials& essentials, bool& quitPause);

}

#endif //ONE_PLAYER_GAME_IN_PAUSE_H