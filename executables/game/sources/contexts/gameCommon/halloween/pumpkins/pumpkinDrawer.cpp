#include "contexts/gameCommon/halloween/pumpkins/pumpkinDrawer.h"
#include "types/essentialsStruct.h"
#include "contexts/gameCommon/halloween/pumpkins/pumpkinCombo.h"
#include <cassert>
#include <algorithm>

PumpkinDrawer::PumpkinDrawer(Essentials& essentials):
	loadedTextures{essentials.logs, essentials.rndWnd, "data/textures/pumpkinTextures_4.txt"},
	draw{loadedTextures}
{
	
}

void PumpkinDrawer::drawPumpkin(Essentials& essentials, const PumpkinCombo& pumpkin)
{
	assert( pumpkin.color < draw.size() );
	draw.drawToCenter(essentials.rndWnd, pumpkin.move.get_x_position(), pumpkin.move.get_y_position(), pumpkin.color );
}

PumpkinDrawer::operator bool() const
{
	return loadedTextures.wasLoadingPerfect();
}

int PumpkinDrawer::getTextureWidth(std::size_t textureIndex) const
{
	assert( textureIndex < loadedTextures.size() );
	return draw.width(textureIndex);
}

int PumpkinDrawer::getTextureHeight(std::size_t textureIndex) const
{
	assert( textureIndex < loadedTextures.size() );
	return draw.height(textureIndex);
}