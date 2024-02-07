#include "levelComponents/inGameBagThings/bonusesCountGraphics.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "texturing/texturePosition.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"
#include "consts/onePlayerBonusesConsts.h"
#include <cassert>

BonusesCountGraphics::BonusesCountGraphics(Essentials& essentials):
	isLoadingPerfect{true},
	fancyFont{essentials.logs.error, FancyFontPath, FontMediumPointSize},
	bonusesCount(onePlGame::BonusMax),
	updateTexts(onePlGame::BonusMax, true)
{	
	
}

void BonusesCountGraphics::drawEverything(Essentials& essentials) const
{
	for( auto const &text : bonusesCount )
	{
		text.draw(essentials.rndWnd);
	}
}

void BonusesCountGraphics::setUpdateFlag(std::size_t bonusNumber)
{
	assert( bonusNumber < onePlGame::BonusMax );
	updateTexts[bonusNumber] = true;
}

void BonusesCountGraphics::updateNeededTexts(Essentials& essentials, const PlayerData& playerData, const std::vector<TextureCombo>& bagIcons)
{
	if( fancyFont )
	{
		for( std::size_t i{0} ; i < onePlGame::BonusMax ; ++i )
		{
			assert( i < bagIcons.size() );
			if( updateTexts[i] )
			{
				bonusesCount[i].texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, std::to_string(playerData.bonusesInBag[i]), WhiteColor);
				bonusesCount[i].resetSpritePosition(TexturePosition{ bagIcons[i].sprite.x_pos() + SQR_SIZE, bagIcons[i].sprite.y_pos() + SQR_SIZE*2, true, true} );
				updateTexts[i] = false;
			}
		}
	}
}