#ifndef GAME_ONE_PLAYER_GAME_DEMO_RECORDING_LVL_SELECTION_INTERFACE_H
#define GAME_ONE_PLAYER_GAME_DEMO_RECORDING_LVL_SELECTION_INTERFACE_H

#include "contexts/onePlayerGame/demoRecording/bonusesBagAndCoinEditBoxes.h"
#include "crossLevel/playerData.h"
#include "levelComponents/demosObjects/demoMainPackage.h"
#include "contexts/onePlayerGame/demoRecording/levelSelectionButtons.h"

namespace onePlGame{

namespace demoRecording{

struct LevelSelection
{
	PlayerData playerData;
	demos::MainPackage demosMainPackage;
	onePlGame::demoRecording::BonusesAndCoinsEdition bonusesAndCoinsEdition;
	onePlGame::demoRecording::LevelsButtons levelsButtons;

	explicit LevelSelection(Essentials& essentials, unsigned campaignType);
	~LevelSelection() = default;
	LevelSelection( const LevelSelection& ) = delete;
	LevelSelection& operator= ( const LevelSelection& ) = delete;
	LevelSelection( LevelSelection&& ) = default;
	LevelSelection& operator= ( LevelSelection&& ) = default;

	void drawEverything(Essentials& essentials) const;
	void updateObjects(Essentials& essentials);
};

}

}

#endif //GAME_ONE_PLAYER_GAME_DEMO_RECORDING_LVL_SELECTION_INTERFACE_H