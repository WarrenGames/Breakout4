#include "contexts/gameCommon/hellSkulls/skullDrawer.h"
#include "types/essentialsStruct.h"
#include "contexts/gameCommon/hellSkulls/skullData.h"
#include "contexts/gameCommon/hellSkulls/skullConsts.h"

HellSkullDrawer::HellSkullDrawer(Essentials& essentials):
	loadedTextures{essentials.logs, essentials.rndWnd, Coord2D{ hellSkull::AnimFramesNumber, hellSkull::TexturesDirectionsNumber}, hellSkull::TexturesListFile },
	drawer{loadedTextures}
{
	
}

bool HellSkullDrawer::wasLoadingPerfect() const
{
	return loadedTextures.wasLoadingPerfect();
}

void HellSkullDrawer::drawHellSkull(Essentials& essentials, const SkullData& hellSkullData)
{
	drawer.drawToCenter(essentials.rndWnd, hellSkullData.frameNumber, hellSkullData.direction, hellSkullData.move.get_x_position(), hellSkullData.move.get_y_position() );
}

int HellSkullDrawer::getTextureWidth(const SkullData& hellSkullData) const
{
	return drawer(hellSkullData.frameNumber, hellSkullData.direction).width();
}

int HellSkullDrawer::getTextureHeight(const SkullData& hellSkullData) const
{
	return drawer(hellSkullData.frameNumber, hellSkullData.direction).height();
}