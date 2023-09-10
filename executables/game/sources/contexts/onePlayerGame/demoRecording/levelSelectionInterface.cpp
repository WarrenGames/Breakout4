#include "contexts/onePlayerGame/demoRecording/levelSelectionInterface.h"
#include "types/essentialsStruct.h"
#include "demos/consts/demosConsts.h"

onePlGame::demoRecording::LevelSelection::LevelSelection(Essentials& essentials, unsigned campaignType):
	playerData{demos::GameIsRecording},
	demosMainPackage{essentials.logs, essentials.prefPath, demos::GameIsRecording},
	bonusesAndCoinsEdition{essentials, playerData},
	levelsButtons{essentials}
{
	playerData.campaignType = campaignType;
	playerData.laterInitialization(essentials.logs);
	levelsButtons.createButtons(essentials, playerData.levelsInfos);
}

void onePlGame::demoRecording::LevelSelection::drawEverything(Essentials& essentials) const
{
	bonusesAndCoinsEdition.drawEverything(essentials);
	levelsButtons.drawCurrentPage(essentials);
}

void onePlGame::demoRecording::LevelSelection::updateObjects(Essentials& essentials)
{
	bonusesAndCoinsEdition.updateBoxesEvents(essentials);
	levelsButtons.updateButtons(essentials);
}