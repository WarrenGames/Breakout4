#include "contexts/gameCommon/stalactites/stalactitesDrawer.h"
#include "contexts/gameCommon/stalactites/stalactitesData.h"
#include "contexts/gameCommon/stalactites/stalactitesConsts.h"
#include "types/essentialsStruct.h"
#include <cassert>
#include <string>

constexpr int TEXTURES_INDEX = 1;
constexpr int RECTS_INDEX = 7;

StalactitesDrawer::StalactitesDrawer(Essentials& essentials):
	loadedTextures{essentials.logs, essentials.rndWnd, stalactites::TEXTURES_FILE_PATH},
	sprites{loadedTextures},
	isLoadingPerfect{true}
{
	
}

void StalactitesDrawer::drawStalactite(Essentials& essentials, const StalactiteData& stalactite)
{
	assert( stalactite.getDirection() < sprites.size() );
	sprites.drawToCenter(essentials.rndWnd, stalactite.getPosition(), stalactite.getDirection() );
}

bool StalactitesDrawer::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

int StalactitesDrawer::getWidth(unsigned stalactiteDirection) const
{
	assert( stalactiteDirection < sprites.size() );
	return sprites.width(stalactiteDirection);
}

int StalactitesDrawer::getHeight(unsigned stalactiteDirection) const
{
	assert( stalactiteDirection < sprites.size() );
	return sprites.height(stalactiteDirection);
}
