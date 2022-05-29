#include "contexts/onePlayerGame/levelEnd/levelEndContext.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "contexts/onePlayerGame/levelComponents/global/globalGameObject.h"
#include "contexts/onePlayerGame/levelEnd/completeLevelInterface.h"
#include "consts/constexprScreen.h"
#include "consts/onePlayerLevelConsts.h"

void levelEnd::startLevelSum(Essentials& essentials, LevelComponents& levelComponents, PlayerData& playerData, bool& quitMainMenu)
{
	if( levelComponents.getLevelEndType() == onePlGame::LEVEL_END_COMPLETE || levelComponents.getLevelEndType() == onePlGame::LEVEL_END_PARTIALLY)
	{
		levelEnd::add400PtsBonus(levelComponents.getLevelEndType(), playerData);
		playerData.setCursorToNextLevel();
		LevelCompleteGUI levelCompleteGUI{essentials};
		levelEnd::levelHasEnded(essentials, levelComponents, levelCompleteGUI);
		levelComponents.recordRimStateToPlayerData(playerData);
		levelComponents.recordRacketLengthToPlayerData(playerData);
	}
	else if( levelComponents.getLevelEndType() == onePlGame::LEVEL_END_SURRENDER )
	{
		LevelCompleteGUI levelCompleteGUI{essentials};
		quitMainMenu = true;
		levelEnd::levelHasEnded(essentials, levelComponents, levelCompleteGUI);
	}
}

void levelEnd::add400PtsBonus(unsigned levelEndType, PlayerData& playerData)
{
	if( levelEndType == onePlGame::LEVEL_END_COMPLETE )
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
	SDL_Delay(SDL_DELAY_TIME);
}

void levelEnd::quitGameSum(Essentials& essentials, bool& quitGameSum)
{
	if( essentials.inp.getKeyState(input::KEYB_RETURN) || essentials.inp.getKeyState(input::KEYB_SPACE) || essentials.inp.getKeyState(input::KEYB_OUT) )
	{
		quitGameSum = true;
		essentials.inp.setKeyStateToFalse(input::KEYB_RETURN);
		essentials.inp.setKeyStateToFalse(input::KEYB_SPACE);
		essentials.inp.setKeyStateToFalse(input::KEYB_OUT);
	}
}