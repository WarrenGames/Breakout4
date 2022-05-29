#include "contexts/duels/matchConfig/zoneChoice/zonesPanels.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "texturing/texturePosition.h"
#include "consts/sdlColors.h"
#include <algorithm>

constexpr int FRAME_WIDTH = SQR_SIZE * 4;
constexpr int FRAME_HEIGHT = SQR_SIZE * 3;

duels::PanelsGraphics::PanelsGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd):
	isLoadingPerfect{ true },
	panelsFrames{
		SDL_Rect{SQR_SIZE, SQR_SIZE, FRAME_WIDTH, FRAME_HEIGHT},
		SDL_Rect{SQR_SIZE*6, SQR_SIZE, FRAME_WIDTH, FRAME_HEIGHT}
	},
	zonesPanels{
		TextureCombo{logs, rndWnd, "textures/gameZones/simple/icoZoneSimple.png", TexturePosition{SQR_SIZE, SQR_SIZE} },
		TextureCombo{logs, rndWnd, "textures/gameZones/halloween/halloweenPanel.png", TexturePosition{SQR_SIZE * 6, SQR_SIZE} },
		TextureCombo{logs, rndWnd, "textures/gameZones/factory/zonePanel.png", TexturePosition{SQR_SIZE * 11, SQR_SIZE} }
	}
{
	isLoadingPerfect = std::all_of(zonesPanels.cbegin(), zonesPanels.cend(), [](auto const& t){ return t.texture.wasLoadingPerfect(); } );
}

duels::PanelsGraphics::operator bool() const
{
	return isLoadingPerfect;
}

void duels::PanelsGraphics::drawPanels(sdl2::RendererWindow& rndWnd) const
{
	drawPictures(rndWnd);
	drawFrames(rndWnd);
}

bool duels::PanelsGraphics::setZoneChoice(const Offset& mousePos, bool leftButtonState, unsigned& zoneIndex) const
{
	for( unsigned i{0} ; i < duels::ZONE_MAX ; ++i )
	{
		if( leftButtonState 
			&& mousePos.x >= zonesPanels[i].sprite.x_pos() && mousePos.x < zonesPanels[i].sprite.x_pos() + zonesPanels[i].sprite.width() 
			&& mousePos.y >= zonesPanels[i].sprite.y_pos() && mousePos.y < zonesPanels[i].sprite.y_pos() + zonesPanels[i].sprite.height() )
		{
			zoneIndex = i;
			return true;
		}
	}
	return false;
}

void duels::PanelsGraphics::drawPictures(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &panel : zonesPanels )
		panel.draw(rndWnd);
}

void duels::PanelsGraphics::drawFrames(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &rect : panelsFrames )
	{
		rndWnd.drawRect(WHITE_COL, rect);
	}
}