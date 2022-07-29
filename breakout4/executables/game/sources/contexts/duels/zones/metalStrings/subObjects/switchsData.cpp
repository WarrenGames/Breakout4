#include "contexts/duels/zones/metalStrings/subObjects/switchsData.h"
#include "types/essentialsStruct.h"
#include "contexts/duels/zones/metalStrings/subObjects/notStringsElements.h"
#include "contexts/duels/instructions/positionCheck.h"
#include "consts/constexprScreen.h"
#include "contexts/duels/duelsConstexpr.h"
#include "contexts/duels/zones/metalStrings/subObjects/consts.h"
#include <string>
#include <cassert>

metalStrings::SwitchsData::SwitchsData(const metalStrings::LevelBricks& levelBricks)
{
	createSwitchesData(levelBricks);
}

const metalStrings::SingleSwitch& metalStrings::SwitchsData::operator [](std::size_t switchNumber) const
{
	assert( switchNumber < switches.size() );
	return switches[switchNumber];
}

metalStrings::SingleSwitch& metalStrings::SwitchsData::operator [](std::size_t switchNumber)
{
	assert( switchNumber < switches.size() );
	return switches[switchNumber];
}

bool metalStrings::SwitchsData::isPlayerOnSwitch(unsigned switchNumber, const SDL_Rect& playerRect) const
{
	assert( switchNumber < switches.size() );
	
	return doesRectsCollide( getRectFromSwitch(switchNumber), playerRect);
}

std::size_t metalStrings::SwitchsData::size() const
{
	return switches.size();
}

void metalStrings::SwitchsData::setSwitchsState(std::size_t switchNumber, unsigned stateEnum)
{
	assert( switchNumber < switches.size() );
	switches[switchNumber].state = stateEnum;
}

void metalStrings::SwitchsData::setPlayerSwitchState(std::size_t playerNum, unsigned stateEnum)
{
	assert( playerNum < duels::PLAYER_MAX && playerNum < switches.size() );
	switches[playerNum].state = stateEnum;
}

void metalStrings::SwitchsData::updateAnimation()
{
	if( animDelay.hasTimeElapsed( std::chrono::milliseconds{50} ) )
	{
		for( auto &data : switches )
		{
			if( data.state == metalStrings::DIR_FORWARD && data.animFrame + 1 < SWITCHS_TEX_NUM )
			{
				data.animFrame++;
			}
			else if( data.state == metalStrings::DIR_REGRESS && data.animFrame > 0 )
			{
				data.animFrame--;
			}
		}
		animDelay.joinTimePoints();
	}
}

SDL_Rect metalStrings::SwitchsData::getRectFromSwitch(unsigned switchNumber) const
{
	assert( switchNumber < switches.size() );
	return SDL_Rect{static_cast<int>(switches[switchNumber].coords.width) * SQR_SIZE, static_cast<int>(switches[switchNumber].coords.height) * SQR_SIZE, SQR_SIZE, SQR_SIZE};
}

void metalStrings::SwitchsData::createSwitchesData(const metalStrings::LevelBricks& levelBricks)
{
	for( std::size_t width{0} ; width < levelBricks.levelGrid.width() ; ++width )
	{
		for( std::size_t height{0} ; height < levelBricks.levelGrid.height() ; ++height )
		{
			if( levelBricks.levelGrid(width, height).index == duels::GRID_ID_BUTTON )
			{
				if( height < GAME_SQUARES_HEIGHT / 2 )
					switches.emplace_back(SingleSwitch{metalStrings::DIR_STOP, Coord2D{width, height}, 0, duels::PLAYER_RED } );
				else
					switches.emplace_back(SingleSwitch{metalStrings::DIR_STOP, Coord2D{width, height}, 0, duels::PLAYER_BLUE } );
			}
		}
	}
}

