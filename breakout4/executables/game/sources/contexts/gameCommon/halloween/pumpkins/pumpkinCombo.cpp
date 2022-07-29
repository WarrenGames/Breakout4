#include "contexts/gameCommon/halloween/pumpkins/pumpkinCombo.h"
#include "contexts/gameCommon/halloween/pumpkins/pumpkinConsts.h"
#include "consts/constexprScreen.h"
#include <cassert>

PumpkinCombo::PumpkinCombo():
	move{},
	direction{PUMPK_STUCK},
	color{PUMPK_RED},
	isEffective{false},
	isFromBat{false}
{
	move.setPosition(Offset{-SQR_SIZE*2, -SQR_SIZE*2});
}

PumpkinCombo::PumpkinCombo(bool isBatPumpkin):
	move{},
	direction{PUMPK_STUCK},
	color{PUMPK_RED},
	isEffective{false},
	isFromBat{isBatPumpkin}
{
	move.setPosition(Offset{-SQR_SIZE*2, -SQR_SIZE*2});
}

PumpkinCombo::PumpkinCombo(const Offset& position, unsigned newColor):
	direction{PUMPK_STUCK},
	color{newColor},
	isEffective{false},
	isFromBat{false}
{
	move.setPosition(position);
}

bool PumpkinCombo::isPumpkinInsideOfScreen(int width, int height)
{
	return move.get_x_position() + width / 2 >= 0
		&& move.get_x_position() - width / 2 < GAME_SCREEN_WIDTH
		&& move.get_y_position() + height / 2 >= 0
		&& move.get_y_position() - height / 2 < GAME_SCREEN_HEIGHT;
}

PumpkinMoveInfo::PumpkinMoveInfo():
	origin{0, 0},
	destination{0, 0},
	pumpkinSpeed{2}
{

}