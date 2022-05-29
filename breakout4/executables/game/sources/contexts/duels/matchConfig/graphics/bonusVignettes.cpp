#include "contexts/duels/matchConfig/graphics/bonusVignettes.h"
#include "consts/constexprScreen.h"

duels::BonusVignettes::BonusVignettes(AppLogFiles& logs, sdl2::RendererWindow& rndWnd):
	vignettes{
		TextureCombo{ logs, rndWnd, "textures/vignettes/duelsVignettes/enlarge.png"},
		TextureCombo{ logs, rndWnd, "textures/vignettes/duelsVignettes/shrink.png"},
		TextureCombo{ logs, rndWnd, "textures/vignettes/duelsVignettes/stuck.png"},
		TextureCombo{ logs, rndWnd, "textures/vignettes/duelsVignettes/steal.png"},
		TextureCombo{ logs, rndWnd, "textures/vignettes/duelsVignettes/speedMore.png"},
		TextureCombo{ logs, rndWnd, "textures/vignettes/duelsVignettes/speedLess.png"},
		TextureCombo{ logs, rndWnd, "textures/vignettes/duelsVignettes/oneMoreBall.png"},
		TextureCombo{ logs, rndWnd, "textures/vignettes/duelsVignettes/special.png"},
		TextureCombo{ logs, rndWnd, "textures/vignettes/duelsVignettes/skull.png"}
	}

{
	setVignettesCoordinates();
}

void duels::BonusVignettes::setVignettesCoordinates()
{
	for( std::size_t i{0} ; i < vignettes.size() ; ++i )
	{
		vignettes[i].sprite.setDefaultCoord(SQR_SIZE, SQR_SIZE * 2 + SQR_SIZE * static_cast<int>(i) );
	}
}

void duels::BonusVignettes::drawVignettes(sdl2::RendererWindow& rndWnd) const
{
	for( const auto &vign : vignettes )
		vign.draw(rndWnd);
}