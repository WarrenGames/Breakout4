#include "contexts/duels/inGameObjects/bonus/bonusDrawer.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "contexts/duels/inGameObjects/playerInputs/inputsConsts.h"
#include <cassert>
#include <algorithm>

BonusDrawer::BonusDrawer(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned playerType):
	textures{
		TextureCombo{logs, rndWnd, "textures/vignettes/duelsVignettes/enlarge.png"},
		TextureCombo{logs, rndWnd, "textures/vignettes/duelsVignettes/shrink.png"},
		TextureCombo{logs, rndWnd, "textures/vignettes/duelsVignettes/stuck.png"},
		TextureCombo{logs, rndWnd, "textures/vignettes/duelsVignettes/steal.png"},
		TextureCombo{logs, rndWnd, "textures/vignettes/duelsVignettes/speedMore.png"},
		TextureCombo{logs, rndWnd, "textures/vignettes/duelsVignettes/speedLess.png"},
		TextureCombo{logs, rndWnd, "textures/vignettes/duelsVignettes/oneMoreBall.png"},
		TextureCombo{logs, rndWnd, "textures/vignettes/duelsVignettes/special.png"},
		TextureCombo{logs, rndWnd, "textures/vignettes/duelsVignettes/skull.png"}
	}
{
	assert( playerType < duels::PLAYER_MAX );
	for( auto &i : textures )
	{
		if( playerType == duels::PLAYER_BLUE )
			i.sprite.setDefaultCoord(SQR_SIZE - i.sprite.width() / 2, GAME_SCREEN_HEIGHT - SQR_SIZE / 2 - i.sprite.height() / 2 );
		else if( playerType == duels::PLAYER_RED )
			i.sprite.setDefaultCoord(SQR_SIZE - i.sprite.width() / 2, SQR_SIZE / 2 - i.sprite.height() / 2 );
	}
}

bool BonusDrawer::wasLoadingPerfect() const
{
	return std::all_of(textures.cbegin(), textures.cend(), [](auto const& texture){ return texture.texture.wasLoadingPerfect(); } );
}

void BonusDrawer::drawBonus(sdl2::RendererWindow& rndWnd, unsigned bonusNumber) const
{
	assert( bonusNumber < duels::DB_MAX );
	textures[bonusNumber].draw(rndWnd);
}