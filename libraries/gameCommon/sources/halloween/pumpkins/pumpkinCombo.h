#ifndef DUELS_PUMPKIN_COMBO_H
#define DUELS_PUMPKIN_COMBO_H

#include "spriteMove/objectMove.h"

struct PumpkinCombo
{
	spriteMove::ObjectMoving move;
	unsigned direction;
	unsigned color;
	bool isEffective;
	bool isFromBat;
	
	explicit PumpkinCombo();
	explicit PumpkinCombo(bool isBatPumpkin);
	explicit PumpkinCombo(const Offset& position, unsigned newColor);
	~PumpkinCombo() = default;
	PumpkinCombo( const PumpkinCombo& ) = default;
	PumpkinCombo& operator= ( const PumpkinCombo& ) = default;
	
	bool isPumpkinInsideOfScreen(int width, int height);
};

struct PumpkinMoveInfo
{
	Offset origin;
	Offset destination;
	double pumpkinSpeed;
	
	PumpkinMoveInfo();
	~PumpkinMoveInfo() = default;
	PumpkinMoveInfo( const PumpkinMoveInfo& ) = default;
	PumpkinMoveInfo& operator= ( const PumpkinMoveInfo& ) = default;
	PumpkinMoveInfo( PumpkinMoveInfo&& ) = default;
	PumpkinMoveInfo& operator= ( PumpkinMoveInfo&& ) = default;
};

#endif //DUELS_PUMPKIN_COMBO_H