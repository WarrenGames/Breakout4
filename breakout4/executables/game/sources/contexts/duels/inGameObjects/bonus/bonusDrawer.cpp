#include "contexts/duels/inGameObjects/bonus/bonusDrawer.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "contexts/duels/inGameObjects/playerInputs/inputsConsts.h"
#include "contexts/duels/duelsConstexpr.h"
#include <cassert>
#include <algorithm>

BonusDrawer::BonusDrawer(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned playerType):
	loadedTextures{logs, rndWnd, "data/textures/duelsBonusVignettes.txt"},
	draw{loadedTextures}
{
	assert( playerType < duels::PLAYER_MAX );
	setTexturesPositions(playerType);
}

bool BonusDrawer::wasLoadingPerfect() const
{
	return loadedTextures.wasLoadingPerfect();
}

void BonusDrawer::drawBonus(sdl2::RendererWindow& rndWnd, unsigned bonusNumber) const
{
	assert( bonusNumber < duels::DB_MAX );
	draw.draw(rndWnd, bonusNumber);
}

void BonusDrawer::setTexturesPositions(unsigned playerType)
{
	for( auto &spr : draw )
	{
		switch( playerType )
		{
			case duels::PLAYER_BLUE:
				spr.center_on_x(SQR_SIZE);
				spr.center_on_y(GAME_SCREEN_HEIGHT - SQR_SIZE / 2 );
				break;
			case duels::PLAYER_RED:
				spr.center_on_x(SQR_SIZE);
				spr.center_on_y(SQR_SIZE / 2);
				break;
			default:
				assert( false && "Error: bad 'playerType' value." );
				break;
		}
	}
}