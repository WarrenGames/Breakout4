#include "duels/matchConfig/graphics/bonusVignettes.h"
#include "consts/constexprScreen.h"

duels::BonusVignettes::BonusVignettes(AppLogFiles& logs, sdl2::RendererWindow& rndWnd):
	loadedTextures{logs, rndWnd, "data/textures/duelsBonusVignettes.txt"},
	draw{loadedTextures}
{
	setVignettesCoordinates();
}

void duels::BonusVignettes::setVignettesCoordinates()
{
	for( std::size_t i{0} ; i < draw.size() ; ++i )
	{
		draw[i].setDefaultCoord(SQR_SIZE, SQR_SIZE * 2 + SQR_SIZE * static_cast<int>(i) );
	}
}

void duels::BonusVignettes::drawVignettes(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &vignette : draw )
	{
		vignette.draw(rndWnd);
	}
}