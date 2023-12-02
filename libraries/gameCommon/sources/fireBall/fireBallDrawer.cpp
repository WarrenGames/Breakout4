#include "fireBall/fireBallDrawer.h"
#include "types/essentialsStruct.h"
#include "fireBall/fireBallDrawData.h"
#include "spriteMove/objectMove.h"
#include "spriteMove/starType.h"
#include "fireBall/fireBallConsts.h"

FireBallDrawer::FireBallDrawer(Essentials& essentials):
	loadedTextures{essentials.logs, essentials.rndWnd, Coord2D{ fireBall::AnimFramesNumber, fireBall::TexturesDirectionsNumber}, fireBall::TexturesListFile },
	drawer{loadedTextures}
{
	
}

bool FireBallDrawer::wasLoadingPerfect() const
{
	return loadedTextures.wasLoadingPerfect();
}

void FireBallDrawer::drawFireBall(Essentials& essentials, const FireBallDrawData& drawData, const spriteMove::ObjectMoving& move, const spriteMove::StarTypeThings& direction)
{
	drawer.drawToCenter(essentials.rndWnd, drawData.frameNumber, direction.getDirPad(), move.get_x_position(), move.get_y_position() );
}