#include "duels/matchConfig/graphics/zonesPanels.h"
#include "texturing/texturePosition.h"
#include "advancedDrawing/interfaceGeneratorLanguage/elementsLoadingFunctions/texturesComponent.h"
#include "consts/constexprScreen.h"
#include <cassert>
#include <algorithm>

ZonesPanels::ZonesPanels(AppLogFiles& logs, sdl2::RendererWindow& rndWnd)
{
	igl::texture::openScriptFileWithImageOnly(logs, rndWnd, panels, "data/interfaceScripts/duelsZonesChoiceScreen.txt", SQR_SIZE);
	
	setAllTexturesPositions();
}

bool ZonesPanels::wasLoadingPerfect() const
{
	return std::all_of(panels.cbegin(), panels.cend(), 
								[](auto const& texture){ return texture.texture.wasLoadingPerfect(); } );;
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

void ZonesPanels::setAllTexturesPositions()
{
	for( auto &combo : panels )
	{
		if( combo )
		{
			combo.resetSpritePosition( TexturePosition{ GameScreenWidth / 2, SQR_SIZE * 9 + SQR_SIZE / 2, true, true } );
		}
	}
}