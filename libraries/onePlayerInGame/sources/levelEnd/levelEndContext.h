#ifndef ONE_PLAYER_LEVEL_END_CONTEXT_H
#define ONE_PLAYER_LEVEL_END_CONTEXT_H

struct Essentials;
struct LevelComponents;
class LevelCompleteGUI;
struct PlayerData;

namespace levelEnd{

void startLevelSum(Essentials& essentials, LevelComponents& levelComponents, PlayerData& playerData, bool& quitMainMenu);

void add400PtsBonus(unsigned levelEndType, PlayerData& playerData);

void levelHasEnded(Essentials& essentials, LevelComponents& levelComponents, const LevelCompleteGUI& levelCompleteGUI);

void update(Essentials& essentials, LevelComponents& levelComponents, const LevelCompleteGUI& levelCompleteGUI, bool& quitGameSum);

void drawEverything(Essentials& essentials, LevelComponents& levelComponents, const LevelCompleteGUI& levelCompleteGUI);

void quitGameSum(Essentials& essentials, bool& quitGameSum);

}

#endif //ONE_PLAYER_LEVEL_END_CONTEXT_H