#ifndef DUELS_PUMPKIN_COMBO_H
#define DUELS_PUMPKIN_COMBO_H

#include "contexts/gameCommon/movements/objectMove.h"

struct PumpkinCombo
{
	ObjectMoving move;
	unsigned direction;
	unsigned color;
	bool isEffective;
	bool isFromBat;
	
	explicit PumpkinCombo();
	explicit PumpkinCombo(bool isBatPumpkin);
	explicit PumpkinCombo(const Offset& position, unsigned newColor);
	bool isPumpkinInsideOfScreen(int width, int height);
};

struct PumpkinMoveInfo
{
	Offset origin;
	Offset destination;
	double pumpkinSpeed;
	
	PumpkinMoveInfo();
};

#endif //DUELS_PUMPKIN_COMBO_H