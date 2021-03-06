#include "contexts/gameCommon/fireBall/fireBallDrawer.h"
#include "types/essentialsStruct.h"
#include "contexts/gameCommon/fireBall/fireBallDrawData.h"
#include "spriteMove/objectMove.h"
#include "spriteMove/starType.h"
#include "contexts/gameCommon/fireBall/fireBallConsts.h"

FireBallDrawer::FireBallDrawer(Essentials& essentials):
	loadedTextures{essentials.logs, essentials.rndWnd, Coord2D{ fireBall::ANIM_FRAMES_NUMBER, fireBall::TEXTURES_DIRECTIONS_NUMBER}, fireBall::TEXTURES_LIST_FILE },
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