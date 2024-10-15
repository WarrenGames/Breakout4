#include "levelComponents/inputs/userInputs.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "levelComponents/demosObjects/demoMainPackage.h"
#include "demos/loading/loadDemosVectorsDataSize.h"
#include "generic/fileSystem/fileProcessing/filesNames.h"
#include "demos/consts/demosConsts.h"
#include "consts/onePlayerLevelConsts.h"
#include <cassert>

LevelInputs::LevelInputs(Essentials& essentials, const PlayerData& playerData):
	demoKind{ playerData.demoKind },
	levelControls{ essentials },
	inputDemoData{ essentials.logs, demos::getVectorsDataSize(essentials.logs, essentials.prefPath, file::DemoInputDataFile), playerData.demoKind, demos::InputDataStr},
	levelEndDemoEvent{ essentials.logs, demos::getVectorsDataSize(essentials.logs, essentials.prefPath, file::DemoQuitEventFile), playerData.demoKind, demos::QuitLevelEventStr}
{

}

void LevelInputs::updateEvents()
{
	switch( demoKind )
	{
		case demos::GameHasPlayerInputs:
			levelControls.updateEvents(nullptr, nullptr);
			playerActions.setActionsWithPlayerInputs(levelControls);
			break;
		case demos::GameIsRecording:
			levelControls.updateEvents(&inputDemoData, &levelEndDemoEvent);
			playerActions.setActionsWithPlayerInputs(levelControls);
			break;
		case demos::GameIsDemo:
			levelControls.updateEvents(nullptr, nullptr);
			playerActions.setActionsWithDemoFile(inputDemoData, levelEndDemoEvent);
			break;
	}
}

void LevelInputs::voidSpecialAction(std::size_t funcEnum)
{
	switch( funcEnum )
	{
		case onePlGame::InputBallTrace:
			levelControls.setKeycodeFalse(onePlGame::InputBallTrace);
			levelControls.setButtonFalse(onePlGame::JoystickButtonBallTrace);
			playerActions.setActionToFalse(onePlGame::InputBallTrace);
			break;
		case onePlGame::InputLookBag:
			levelControls.setKeycodeFalse(onePlGame::InputLookBag);
			levelControls.setButtonFalse(onePlGame::JoystickButtonSearchBag);
			playerActions.setActionToFalse(onePlGame::InputLookBag);
			break;
		case onePlGame::InputSwitch:
			levelControls.setKeycodeFalse(onePlGame::InputSwitch);
			levelControls.setButtonFalse(onePlGame::JoystickButtonSwitch);
			playerActions.setActionToFalse(onePlGame::InputSwitch);
			break;
	}
}

bool LevelInputs::doesUserCloseWindow() const
{
	return playerActions.getQuitActionFlag() || levelControls.windowAskedToBeClosed();
}

void LevelInputs::setEscapeToFalse()
{
	playerActions.setQuitActionFlagToFalse();
}

const Offset& LevelInputs::getMousePosition() const
{
	return levelControls.getMousePosition();
}

bool LevelInputs::getMouseButtonState(std::size_t buttonIndex) const
{
	return levelControls.getMouseButton(buttonIndex);
}

bool LevelInputs::getFuncState(std::size_t funcEnum) const
{
	return playerActions.getActionState(funcEnum);
}

unsigned LevelInputs::getCrossMoveDeviceType() const
{
	return levelControls.getCrossMoveDeviceType();
}

const Offset& LevelInputs::getCrossMove() const
{
	return levelControls.getCrossMove();
}

SDL_Keycode LevelInputs::getLastKeycode() const
{
	return levelControls.getLastKeycode();
}

void LevelInputs::cancelLastKeycode()
{
	levelControls.cancelLastKeycode();
}

void LevelInputs::joinDemosTimePoints()
{
	playerActions.joinDemosTimePoint();
	levelControls.joinDemosTimePoint();
	inputDemoData.setPrecedentTimePoint();
	levelEndDemoEvent.setPrecedentTimePoint();
}

void LevelInputs::moveMainPackageToInputs(demos::MainPackage& demosMainPackage)
{
	inputDemoData = std::move( demosMainPackage.inputData );
	levelEndDemoEvent = std::move( demosMainPackage.quitLevelEvent );
}

void LevelInputs::giveStacksContentsToMainPackage(demos::MainPackage& demosMainPackage)
{
	demosMainPackage.inputData = std::move( inputDemoData );
	demosMainPackage.quitLevelEvent = std::move( levelEndDemoEvent );
}

void LevelInputs::addQuitEvent()
{
	levelControls.recordSdlQuitForDemo(&levelEndDemoEvent);
}