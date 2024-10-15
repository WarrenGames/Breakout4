#include "levelEnd/levelEndContext.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "levelComponents/global/globalGameObject.h"
#include "levelEnd/completeLevelInterface.h"
#include "consts/constexprScreen.h"
#include "consts/onePlayerLevelConsts.h"

void levelEnd::startLevelSum(Essentials& essentials, LevelComponents& levelComponents, PlayerData& playerData, bool& quitMainMenu)
{
	if( levelComponents.getLevelEndType() == onePlGame::LevelEndComplete || levelComponents.getLevelEndType() == onePlGame::LevelEndPartially)
	{
		levelEnd::add400PtsBonus(levelComponents.getLevelEndType(), playerData);
		playerData.setCursorToNextLevel();
		LevelCompleteGUI levelCompleteGUI{essentials};
		levelEnd::levelHasEnded(essentials, levelComponents, levelCompleteGUI);
		levelComponents.recordRimStateToPlayerData(playerData);
		levelComponents.recordRacketLengthToPlayerData(playerData);
		levelComponents.recordRacketSpeedToPlayerData(playerData);
	}
	else if( levelComponents.getLevelEndType() == onePlGame::LevelEndSurrender )
	{
		LevelCompleteGUI levelCompleteGUI{essentials};
		quitMainMenu = true;
		levelEnd::levelHasEnded(essentials, levelComponents, levelCompleteGUI);
	}
}

void levelEnd::add400PtsBonus(unsigned levelEndType, PlayerData& playerData)
{
	if( levelEndType == onePlGame::LevelEndComplete )
	{
		playerData.score += 400; 
	}
}

void levelEnd::levelHasEnded(Essentials& essentials, LevelComponents& levelComponents, const LevelCompleteGUI& levelCompleteGUI)
{
	bool quitGameSum{false};
	while( false == quitGameSum )
	{
		levelEnd::update(essentials, levelComponents, levelCompleteGUI, quitGameSum);
	}
}

void levelEnd::update(Essentials& essentials, LevelComponents& levelComponents, const LevelCompleteGUI& levelCompleteGUI, bool& quitGameSum)
{
	essentials.inp.updateEvents();
	levelEnd::quitGameSum(essentials, quitGameSum);
	levelEnd::drawEverything(essentials, levelComponents, levelCompleteGUI);
}

void levelEnd::drawEverything(Essentials& essentials, LevelComponents& levelComponents, const LevelCompleteGUI& levelCompleteGUI)
{
	levelComponents.drawEverything(essentials);
	levelCompleteGUI.drawLevelSum(essentials, levelComponents.getLevelEndType() );
	essentials.rndWnd.displayRenderer();
	SDL_Delay(SdlDelayTime);
}

void levelEnd::quitGameSum(Essentials& essentials, bool& quitGameSum)
{
	if( essentials.inp.getKeyState(input::KeybReturn) || essentials.inp.getKeyState(input::KeybSpace) || essentials.inp.getKeyState(input::KeybOut) )
	{
		quitGameSum = true;
		essentials.inp.setKeyStateToFalse(input::KeybReturn);
		essentials.inp.setKeyStateToFalse(input::KeybSpace);
		essentials.inp.setKeyStateToFalse(input::KeybOut);
	}
}