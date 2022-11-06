#include "contexts/onePlayerGame/levelComponents/inputs/joystickInputData.h"
#include "types/essentialsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include <fstream>
#include <cassert>

onePlGame::JoystickInputData::JoystickInputData(Essentials& essentials):
	isLoadingPerfect{true},
	joystickEntity{ 0 },
	joystickNumber{0},
	joyMoveType{onePlGame::JoystickMoveAxes},
	axisOrHatNum{0},
	axisMoveThreshold{4000},
	joyButtons{0, 1, 2},
	crossMoveType{onePlGame::JoystickMoveAxes},
	crossNum{2, 3}
{
	readJoystickData(essentials);
	readDestCrossJoystickData(essentials);
	
	assert( joyButtons.size() == onePlGame::JoysticButtonMax );//Checks the developper correctly sized the std::vector
	assert( crossNum.size() == onePlGame::JoystickCrossMoveMax );//Checks the developper correctly sized the std::vector
}

void onePlGame::JoystickInputData::readJoystickData(Essentials& essentials)
{
	if( std::ifstream joystickFile{ path::getConfigDirFile(essentials.prefPath, file::ONE_PLAY_JOY_INI) } )
	{
		if( !( joystickFile >> joystickNumber >> joyMoveType >> axisOrHatNum >> axisMoveThreshold 
							>> joyButtons[onePlGame::JoysticButtonBallTrace] >> joyButtons[onePlGame::JoysticButtonSearchBag] >> joyButtons[onePlGame::JoysticButtonSwitch] ) )
		{
			essentials.logs.error << "Error: failed to read data in '" << path::getConfigDirFile(essentials.prefPath, file::ONE_PLAY_JOY_INI) << "' file for one player joystick configuration.\n";
			isLoadingPerfect = false;
		}
	}
	else{
		essentials.logs.error << "Error: couldn't open '" << path::getConfigDirFile(essentials.prefPath, file::ONE_PLAY_JOY_INI) << "' file in order to read the one player joystick data.\n";
		isLoadingPerfect = false;
	}
}

void onePlGame::JoystickInputData::writeJoystickFile(Essentials& essentials)
{
	if( std::ofstream joystickFile{ path::getConfigDirFile(essentials.prefPath, file::ONE_PLAY_JOY_INI) } )
	{
		essentials.logs.error << "Opening '" << path::getConfigDirFile(essentials.prefPath, file::ONE_PLAY_JOY_INI) << "' file to save one player game joystick config data.\n";
		if( !( joystickFile << joystickNumber << " " << joyMoveType << " " << axisOrHatNum << " " << axisMoveThreshold << " " 
							<< joyButtons[onePlGame::JoysticButtonBallTrace] << " " << joyButtons[onePlGame::JoysticButtonSearchBag] << " " << joyButtons[onePlGame::JoysticButtonSwitch] ) )
		{
			essentials.logs.error << "Error: failed to write data in '" << path::getConfigDirFile(essentials.prefPath, file::ONE_PLAY_JOY_INI) 
									<< "' file for one player game joystick configuration.\n";
		}
	}
	else{
		essentials.logs.error << "Error: couldn't open '" << path::getConfigDirFile(essentials.prefPath, file::ONE_PLAY_JOY_INI) << "' file in order to write the one player game joystick data.\n";
	}
}

void onePlGame::JoystickInputData::readDestCrossJoystickData(Essentials& essentials)
{
	if( std::ifstream joyCrossMoveFile{ path::getConfigDirFile(essentials.prefPath, file::CROSS_JOY_MOVE) } )
	{
		if( !( joyCrossMoveFile >> crossMoveType >> crossNum[onePlGame::JoystickCrossMoveX] >> crossNum[onePlGame::JoystickCrossMoveY] ) )
		{
			isLoadingPerfect = false;
			essentials.logs.error << "Error: failed to read data in '" << path::getConfigDirFile(essentials.prefPath, file::CROSS_JOY_MOVE) << "' file for one player joystick configuration.\n";
		}
	}
	else{
		isLoadingPerfect = false;
		essentials.logs.error << "Error: couldn't open '" << path::getConfigDirFile(essentials.prefPath, file::CROSS_JOY_MOVE) << "' file in order to read the one player joystick data.\n";
	}
}

void onePlGame::JoystickInputData::writeDestCrossJoystickFile(Essentials& essentials)
{
	if( std::ofstream joyCrossMoveFile{ path::getConfigDirFile(essentials.prefPath, file::CROSS_JOY_MOVE) } )
	{
		if( !( joyCrossMoveFile << crossMoveType << " " << crossNum[onePlGame::JoystickCrossMoveX] << " " << crossNum[onePlGame::JoystickCrossMoveY] ) )
		{
			essentials.logs.error << "Error: failed to write data in '" << path::getConfigDirFile(essentials.prefPath, file::CROSS_JOY_MOVE)<< "' file for one player game joystick configuration.\n";
		}
	}
	else{
		essentials.logs.error << "Error: couldn't open '" << path::getConfigDirFile(essentials.prefPath, file::CROSS_JOY_MOVE) << "' file in order to write the one player game joystick data.\n";
	}
}