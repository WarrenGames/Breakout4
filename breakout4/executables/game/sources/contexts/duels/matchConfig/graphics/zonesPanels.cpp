#include "contexts/duels/matchConfig/graphics/zonesPanels.h"
#include "texturing/texturePosition.h"
#include "consts/constexprScreen.h"
#include <cassert>
#include <algorithm>

ZonesPanels::ZonesPanels(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, int center_x_pos, int center_y_pos):
	isLoadingPerfect{ true },
	panels{
		TextureCombo{logs, rndWnd, "textures/gameZones/simple/icoZoneSimple.png", TexturePosition{center_x_pos, center_y_pos, true, true } },
		TextureCombo{logs, rndWnd, "textures/gameZones/halloween/halloweenPanel.png", TexturePosition{center_x_pos, center_y_pos, true,true } },
		TextureCombo{logs, rndWnd, "textures/gameZones/factory/zonePanel.png", TexturePosition{center_x_pos, center_y_pos, true, true } }
	}
{
	isLoadingPerfect = std::all_of(panels.cbegin(), panels.cend(), 
								[](auto const& texture){ return texture.texture.wasLoadingPerfect(); } );
}

bool ZonesPanels::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

void ZonesPanels::drawPanel(sdl2::RendererWindow& rndWnd, std::size_t panelIndex) const
{
	assert( panelIndex < panels.size() );
	panels[panelIndex].draw(rndWnd);
}

bool ZonesPanels::isMouseOverCurrentPanel(const Offset& mousePosition, std::size_t panelIndex) const
{
	assert( panelIndex < panels.size() );
	return mousePosition.x >= panels[panelIndex].sprite.x_pos() && mousePosition.x < panels[panelIndex].sprite.x_pos() + panels[panelIndex].sprite.width() 
		&& mousePosition.y >= panels[panelIndex].sprite.y_pos() && mousePosition.y < panels[panelIndex].sprite.y_pos() + panels[panelIndex].sprite.height();
}