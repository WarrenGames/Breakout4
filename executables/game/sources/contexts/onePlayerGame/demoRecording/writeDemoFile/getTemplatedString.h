#ifndef GAME_ONE_PLAYER_GAME_DEMO_RECORDING_WRITE_DEMO_TEMPLATED_STRING_H
#define GAME_ONE_PLAYER_GAME_DEMO_RECORDING_WRITE_DEMO_TEMPLATED_STRING_H

#include "demos/templates/demoStack.h"
#include "consts/sdlColors.h"
#include <string>

template<typename T>
std::string getSizeFlag(const demos::Stack< T >& demosStack, const std::string& stackName)
{
	if( demosStack.getSizeFlag() )
	{
		return std::string{"Stack '" + stackName + "'has enough size: " + std::to_string( demosStack.getCommandsNumber() ) + " current elements."};
	}
	else{
		return std::string{"Stack '" + stackName + "' had not enough size: " + std::to_string( demosStack.getCommandsNumber() ) + " current elements."};
	}
}

template<typename T>
SDL_Color getColor(const demos::Stack< T >& demosStack)
{
	if( demosStack.getSizeFlag() )
	{
		return WhiteColor;
	}
	else{
		return RedColor;
	}
}

#endif //GAME_ONE_PLAYER_GAME_DEMO_RECORDING_WRITE_DEMO_TEMPLATED_STRING_H