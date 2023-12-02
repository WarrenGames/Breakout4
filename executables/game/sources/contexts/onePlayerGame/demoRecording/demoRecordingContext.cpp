#include "contexts/onePlayerGame/demoRecording/demoRecordingContext.h"
#include "contexts/onePlayerGame/demoRecording/demoRecordingInterface.h"
#include "contexts/onePlayerGame/demoRecording/levelSelectionInterface.h"
#include "types/essentialsStruct.h"
#include "levelsContexts/stdLevelContext.h"
#include "levelsContexts/antarcticContext.h"
#include "levelsContexts/hellContext.h"
#include "demosLoadingAndSaving/saving/saveDemoFile.h"
#include "contexts/onePlayerGame/skillLevelChoice/skillLevelChoiceContext.h"
#include "contexts/onePlayerGame/demoRecording/writeDemoFile/writeDemoFileContext.h"
#include "consts/sdlColors.h"
#include "consts/onePlayerLevelConsts.h"

void onePlGame::demoRecording::contextsList(Essentials& essentials)
{
	unsigned campaignType{onePlGame::CampaignMax};
	bool quitWholeContext{false};
	onePlGame::demoRecording::mainContext(essentials, campaignType, quitWholeContext);
	
	onePlGame::demoRecording::levelChoice(essentials, campaignType, quitWholeContext);
}

void onePlGame::demoRecording::mainContext(Essentials& essentials, unsigned& campaignType, bool& quitWholeContext)
{
	onePlGame::demoRecording::Interface interface{essentials};
	
	onePlGame::demoRecording::campaignChoiceMainLoop(essentials, interface, campaignType, quitWholeContext);
}

void onePlGame::demoRecording::campaignChoiceMainLoop(Essentials& essentials, onePlGame::demoRecording::Interface& interface, unsigned& campaignType, bool& quitWholeContext)
{
	while( false == interface.quitMenu && false == quitWholeContext )
	{
		essentials.inp.updateEvents();
		interface.interface.updateInterfaceWithInput(essentials);
		onePlGame::demoRecording::quitChoice(essentials, quitWholeContext);
		onePlGame::demoRecording::shopCampaignSelection(interface, campaignType);
		onePlGame::demoRecording::noShopCampaignSelection(interface, campaignType);
		onePlGame::demoRecording::drawCampaignChoice(essentials, interface);
	}
}

void onePlGame::demoRecording::quitChoice(Essentials& essentials, bool& quitWholeContext)
{
	if( essentials.inp.getKeyState(input::KeybOut) || essentials.inp.getSDL_quit() )
	{
		quitWholeContext = true;
		essentials.inp.setKeyStateToFalse(input::KeybOut);
	}
}

void onePlGame::demoRecording::shopCampaignSelection(onePlGame::demoRecording::Interface& interface, unsigned& campaignType)
{
	if( interface.interface.shopRaceSelection.buttonClicked() )
	{
		interface.quitMenu = true;
		campaignType = onePlGame::CampaignWithShop;
	}
}

void onePlGame::demoRecording::noShopCampaignSelection(onePlGame::demoRecording::Interface& interface, unsigned& campaignType)
{
	if( interface.interface.noShopRaceSelection.buttonClicked() )
	{
		interface.quitMenu = true;
		campaignType = onePlGame::CampaignNoShop;
	}
}

void onePlGame::demoRecording::drawCampaignChoice(Essentials& essentials, const onePlGame::demoRecording::Interface& interface)
{
	if( false == interface.quitMenu )
	{
		if( essentials.drawFreq.canDrawGame() )
		{
			essentials.rndWnd.clearScreen(BlackColor);
			interface.interface.drawInterface(essentials);
			essentials.rndWnd.displayRenderer();
		}
	}
}

void onePlGame::demoRecording::levelChoice(Essentials& essentials, unsigned& campaignType, bool& quitWholeContext)
{
	if( false == quitWholeContext )
	{
		onePlGame::demoRecording::LevelSelection levelSelection{essentials, campaignType};

		onePlGame::demoRecording::levelChoiceMainLoop(essentials, levelSelection, quitWholeContext);
	}
}

void onePlGame::demoRecording::levelChoiceMainLoop(Essentials& essentials, onePlGame::demoRecording::LevelSelection& levelSelection, bool& quitWholeContext)
{
	while( false == quitWholeContext )
	{
		essentials.inp.updateEvents();
		onePlGame::demoRecording::quitChoice(essentials, quitWholeContext);
		levelSelection.updateObjects(essentials);
		onePlGame::demoRecording::drawLevelChoice(essentials, levelSelection, quitWholeContext);
		onePlGame::demoRecording::runDemoRecording(essentials, levelSelection, quitWholeContext);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void onePlGame::demoRecording::drawLevelChoice(Essentials& essentials, const onePlGame::demoRecording::LevelSelection& levelSelection, bool& quitWholeContext)
{
	if( false == quitWholeContext )
	{
		if( essentials.drawFreq.canDrawGame() )
		{
			essentials.rndWnd.clearScreen(BlackColor);
			levelSelection.drawEverything(essentials);
			essentials.rndWnd.displayRenderer();
		}
	}
}

void onePlGame::demoRecording::runDemoRecording(Essentials& essentials, onePlGame::demoRecording::LevelSelection& levelSelection, bool& quitWholeContext)
{
	for( std::size_t i{0} ; i < levelSelection.playerData.levelsInfos.size() ; ++i )
	{
		if( levelSelection.levelsButtons.isButtonClicked(i) )
		{
			onePlGame::skillChoice::context(essentials, levelSelection.playerData.skillLevel, quitWholeContext);
			if( quitWholeContext == false )
			{
				levelSelection.playerData.levelIndex = i;
				onePlGame::demoRecording::setSomeStartingData(levelSelection);
				switch( levelSelection.playerData.getLevelType() )
				{
					case onePlGame::EpisodeSimple:
						stdlevel::startWithDemoRecording(essentials, levelSelection.playerData, levelSelection.demosMainPackage, quitWholeContext);
						break;
					case onePlGame::EpisodeArtic:
						antarcticLevel::startWithDemoRecording(essentials, levelSelection.playerData, levelSelection.demosMainPackage, quitWholeContext);
						break;
					case onePlGame::EpisodeHell:
						hellLevel::startWithDemoRecording(essentials, levelSelection.playerData, levelSelection.demosMainPackage, quitWholeContext);
						break;
				}
				demos::writeDemoFileMainContext(essentials, levelSelection.playerData, levelSelection.demosMainPackage);
			}
		}
	}
}

void onePlGame::demoRecording::setSomeStartingData(onePlGame::demoRecording::LevelSelection& levelSelection)
{
	levelSelection.demosMainPackage.startingData.campaignType = levelSelection.playerData.campaignType;
	levelSelection.demosMainPackage.startingData.levelIndex = static_cast<unsigned>(levelSelection.playerData.levelIndex);
	levelSelection.demosMainPackage.startingData.skillLevel = levelSelection.playerData.skillLevel;
	levelSelection.demosMainPackage.startingData.playerLives = levelSelection.playerData.playerLives;
	levelSelection.demosMainPackage.startingData.racketSize = levelSelection.playerData.racketSize;
	levelSelection.demosMainPackage.startingData.score = levelSelection.playerData.score;
	levelSelection.demosMainPackage.startingData.bonusCoinsNumber = levelSelection.playerData.bonusCoinsNumber;
	levelSelection.demosMainPackage.startingData.rimsStartState = levelSelection.playerData.rimsStartState;
	levelSelection.demosMainPackage.startingData.racketSpeed = levelSelection.playerData.racketSpeed;
	levelSelection.demosMainPackage.startingData.bonusesInBag = levelSelection.playerData.bonusesInBag;
}