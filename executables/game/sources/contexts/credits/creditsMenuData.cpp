#include "contexts/credits/creditsMenuData.h"
#include "texturing/texturePosition.h"
#include "types/essentialsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/fontsConsts.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include <algorithm>

constexpr std::size_t TextsNumber = 9;

creditsMenu::GraphicsData::GraphicsData(Essentials& essentials):
	texts{essentials.logs.error, path::getLanguageFile(essentials.language, file::CREDITS_TEXTS ), TextsNumber},
	arial{essentials.logs.error, ArialFontPath, FontMediumPointSize}
{
	int ypos{SQR_SIZE * 2};
	for( const auto &txt : texts )
	{
		graphicsTexts.emplace_back( TextureCombo{ essentials.logs, essentials.rndWnd, arial, txt, WhiteColor, TexturePosition{Offset{SQR_SIZE, ypos}, false, true} } );
		ypos += SQR_SIZE;
	}
	if( TextsNumber == graphicsTexts.size() )
	{
		graphicsTexts[0].sprite.center_on_x( GameScreenWidth / 2);
		graphicsTexts[0].sprite.center_on_y( SQR_SIZE);
	}
}

void creditsMenu::GraphicsData::drawEverything(Essentials& essentials) const
{
	std::for_each(graphicsTexts.cbegin(), graphicsTexts.cend(), [&essentials](const auto &txt ){ txt.draw(essentials.rndWnd); } );
}