#include "duels/matchConfig/zoneChoice/zonesChoicePanels.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "texturing/texturePosition.h"
#include "advancedDrawing/interfaceGeneratorLanguage/elementsLoadingFunctions/texturesComponent.h"
#include "consts/sdlColors.h"
#include "consts/constexprScreen.h"
#include <algorithm>

duels::PanelsGraphics::PanelsGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd)
{
	igl::texture::openScriptFileWithImageOnly(logs, rndWnd, zonesPanels, "data/interfaceScripts/duelsZonesChoiceScreen.txt", SQR_SIZE);
}

duels::PanelsGraphics::operator bool() const
{
	return std::all_of(zonesPanels.cbegin(), zonesPanels.cend(), [](auto const& t){ return t.texture.wasLoadingPerfect(); } );
}

void duels::PanelsGraphics::drawPanels(sdl2::RendererWindow& rndWnd) const
{
	drawPictures(rndWnd);
	drawFrames(rndWnd);
}

bool duels::PanelsGraphics::setZoneChoice(const Offset& mousePos, bool leftButtonState, unsigned& zoneIndex) const
{
	for( std::size_t i{0} ; i < zonesPanels.size() ; ++i )
	{
		if( leftButtonState 
			&& mousePos.x >= zonesPanels[i].sprite.x_pos() && mousePos.x < zonesPanels[i].sprite.x_pos() + zonesPanels[i].sprite.width() 
			&& mousePos.y >= zonesPanels[i].sprite.y_pos() && mousePos.y < zonesPanels[i].sprite.y_pos() + zonesPanels[i].sprite.height() )
		{
			zoneIndex = static_cast<unsigned>(i);
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
	SDL_Rect rect;
	for( auto const &combo : zonesPanels )
	{
		rect.x = combo.sprite.x_pos();
		rect.y = combo.sprite.y_pos();
		rect.w = combo.sprite.width();
		rect.h = combo.sprite.height();
		rndWnd.drawRect(WhiteColor, rect);
	}
}