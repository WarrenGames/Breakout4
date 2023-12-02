#include "halloween/pumpkins/pumpkinCombo.h"
#include "halloween/pumpkins/pumpkinConsts.h"
#include "consts/constexprScreen.h"
#include <cassert>

PumpkinCombo::PumpkinCombo():
	move{},
	direction{PumpkinStuck},
	color{PumpkinColorRed},
	isEffective{false},
	isFromBat{false}
{
	move.setPosition(Offset{-SQR_SIZE*2, -SQR_SIZE*2});
}

PumpkinCombo::PumpkinCombo(bool isBatPumpkin):
	move{},
	direction{PumpkinStuck},
	color{PumpkinColorRed},
	isEffective{false},
	isFromBat{isBatPumpkin}
{
	move.setPosition(Offset{-SQR_SIZE*2, -SQR_SIZE*2});
}

PumpkinCombo::PumpkinCombo(const Offset& position, unsigned newColor):
	direction{PumpkinStuck},
	color{newColor},
	isEffective{false},
	isFromBat{false}
{
	move.setPosition(position);
}

bool PumpkinCombo::isPumpkinInsideOfScreen(int width, int height)
{
	return move.get_x_position() + width / 2 >= 0
		&& move.get_x_position() - width / 2 < GameScreenWidth
		&& move.get_y_position() + height / 2 >= 0
		&& move.get_y_position() - height / 2 < GameScreenHeight;
}

PumpkinMoveInfo::PumpkinMoveInfo():
	origin{0, 0},
	destination{0, 0},
	pumpkinSpeed{2}
{

}