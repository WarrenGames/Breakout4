#include "contexts/gameCommon/stalactites/stalactitesDrawer.h"
#include "contexts/gameCommon/stalactites/stalactitesData.h"
#include "contexts/gameCommon/stalactites/stalactitesConsts.h"
#include "types/essentialsStruct.h"
#include <cassert>
#include <string>

StalactitesDrawer::StalactitesDrawer(Essentials& essentials):
	loadedTextures{essentials.logs, essentials.rndWnd, stalactites::TexturesFilePath},
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
