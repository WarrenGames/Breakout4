#include "contexts/gameCommon/halloween/pumpkins/pumpkinDrawer.h"
#include "types/essentialsStruct.h"
#include "contexts/gameCommon/halloween/pumpkins/pumpkinCombo.h"
#include <cassert>
#include <algorithm>

PumpkinDrawer::PumpkinDrawer(Essentials& essentials):
	textures{
		TextureCombo{essentials.logs, essentials.rndWnd, "textures/gameZones/halloween/pumpkinRed.png"},
		TextureCombo{essentials.logs, essentials.rndWnd, "textures/gameZones/halloween/pumpkinGray.png"},
		TextureCombo{essentials.logs, essentials.rndWnd, "textures/gameZones/halloween/pumpkinBlue.png"},
		TextureCombo{essentials.logs, essentials.rndWnd, "textures/gameZones/halloween/pumpkinYellow.png"}
	},
	isLoadingPerfect{true}
{
	isLoadingPerfect = std::all_of(textures.cbegin(), textures.cend(), [](auto &tex){ return tex.texture.wasLoadingPerfect(); } );
}

void PumpkinDrawer::drawPumpkin(Essentials& essentials, const PumpkinCombo& pumpkin)
{
	assert( pumpkin.color < textures.size() );
	textures[pumpkin.color].drawToCenter(essentials.rndWnd, pumpkin.move.get_x_position(), pumpkin.move.get_y_position() );
}

PumpkinDrawer::operator bool() const
{
	return isLoadingPerfect;
}

int PumpkinDrawer::getTextureWidth(std::size_t textureIndex) const
{
	assert( textureIndex < textures.size() );
	return textures[textureIndex].sprite.width();
}

int PumpkinDrawer::getTextureHeight(std::size_t textureIndex) const
{
	assert( textureIndex < textures.size() );
	return textures[textureIndex].sprite.height();
}