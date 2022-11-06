#ifndef SPRITES_ORIENTATION_AND_ROTATION_H
#define SPRITES_ORIENTATION_AND_ROTATION_H

#include "customTypes/positionTypes.h"

namespace spriteMove{

long int getDirection(int directionsNumber, int xNorm, int yNorm);

Offset getDirectionVectors(int directionsNumber, int direction, int squareSize);

}

#endif //SPRITES_ORIENTATION_AND_ROTATION_H