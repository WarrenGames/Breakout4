#include "contexts/onePlayerGame/levelComponents/infoBar/infoBar.h"
#include "texts/textLoader.h"
#include "crossLevel/playerData.h"
#include "contexts/gameCommon/rackets/racketData.h"
#include "texturing/texturePosition.h"
#include "types/essentialsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"
#include <cassert>
#include <algorithm>

InfoBar::InfoBar(Essentials& essentials):
	isLoadingPerfect{ true },
	fancyFont{essentials.logs.error, FancyFontPath, FontMediumPointSize},
	brickTexture{essentials.logs, essentials.rndWnd, "textures/sprites/bricks/bricksCluster_game.png"},
	barTexts( infoBarTexts::Max ),
	blackSquares( infoBarTexts::Max ),
	isGraphicalTextUpdateNeeded( infoBarTexts::Max, true ),
	dataTexts( infoBarTexts::Max )
{
	createGraphicalBarTexts(essentials);
	createBlackSquares(essentials, infoBarTexts::BallsInBag, barTexts[infoBarTexts::BallsInBag].sprite.getDrawRect(), SQR_SIZE / 4 );
	createBlackSquares(essentials, infoBarTexts::PlayerScore, barTexts[infoBarTexts::PlayerScore].sprite.getDrawRect(), SQR_SIZE / 4 );
	createBlackSquares(essentials, infoBarTexts::RacketSpeed, barTexts[infoBarTexts::RacketSpeed].sprite.getDrawRect(), SQR_SIZE * 3 / 4 );
	createBlackSquares(essentials, infoBarTexts::BonusCoinNumber, barTexts[infoBarTexts::BonusCoinNumber].sprite.getDrawRect(), SQR_SIZE * 3 / 4 );
	
	if( !( fancyFont && areAllTexturesAllocated() ) )
		isLoadingPerfect = false;
}

InfoBar::operator bool() const 
{
	return isLoadingPerfect;
}

void InfoBar::drawEverything(sdl2::RendererWindow& rndWnd)
{
	drawBricksTextures(rndWnd);
	drawAllBlackSquares(rndWnd);
	drawAllTexts(rndWnd);
	drawData(rndWnd);
}

void InfoBar::updateDataTexts(Essentials& essentials, const PlayerData& playerData, const RacketData& racketData)
{
	updateText(essentials, playerData.playerLives, infoBarTexts::BallsInBag, YellowColor, Offset{blackSquares[infoBarTexts::BallsInBag].sprite.x_pos() + SQR_SIZE/4, SQR_SIZE/4} );
	updateText(essentials, playerData.score, infoBarTexts::PlayerScore, RedColor, Offset{blackSquares[infoBarTexts::PlayerScore].sprite.x_pos() + SQR_SIZE/4, SQR_SIZE/4});
	updateText(essentials, racketData.getSpeed(), infoBarTexts::RacketSpeed, CyanColor, Offset{blackSquares[infoBarTexts::RacketSpeed].sprite.x_pos() + SQR_SIZE/4, SQR_SIZE*3/4});
	updateText(essentials, playerData.bonusCoinsNumber, infoBarTexts::BonusCoinNumber, GreenColor, Offset{blackSquares[infoBarTexts::BonusCoinNumber].sprite.x_pos() + SQR_SIZE/4, SQR_SIZE*3/4});
}

void InfoBar::setUpdateFlag(std::size_t index)
{
	assert( index < infoBarTexts::Max );
	isGraphicalTextUpdateNeeded[index] = true;
}

void InfoBar::updateEverything()
{
	std::fill(isGraphicalTextUpdateNeeded.begin(), isGraphicalTextUpdateNeeded.end(), true);
}

void InfoBar::createGraphicalBarTexts(Essentials& essentials)
{
	if( fancyFont )
	{
		if( const TextsBlocks infosBarLangTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::ONE_PLAY_INFO_BAR), infoBarTexts::Max} )
		{
			std::vector< Offset > textsPositions{ Offset{ SQR_SIZE, SQR_SIZE/4}, 
																	Offset{ GameScreenWidth/2 + SQR_SIZE, SQR_SIZE/4},
																	Offset{ SQR_SIZE, SQR_SIZE * 3 / 4}, 
																	Offset{ GameScreenWidth/2 + SQR_SIZE, SQR_SIZE * 3 /4} };
			assert( textsPositions.size() == infoBarTexts::Max );
			for( std::size_t i{0} ; i < infoBarTexts::Max ; ++i )
			{
				barTexts[i].texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, infosBarLangTexts[i], YellowColor);
				barTexts[i].resetSpritePosition( TexturePosition{textsPositions[i], false, true} );
				if( !barTexts[i].texture )
				{
					isLoadingPerfect = false;
				}
			}
		}
	}
}

void InfoBar::createBlackSquares(Essentials& essentials, std::size_t index, const SDL_Rect& rect, int y_center)
{
	blackSquares[index].texture.loadTextureSquare(essentials.logs, essentials.rndWnd, BlackColor, SQR_SIZE * 4, SQR_SIZE* 3 / 8 );
	blackSquares[index].resetSpritePosition( TexturePosition{rect.x + rect.w + SQR_SIZE / 2, y_center, false, true} );
}

bool InfoBar::areAllTexturesAllocated() const
{
	return brickTexture.texture 
		&& std::all_of(barTexts.cbegin(), barTexts.cend(), [](auto &texture){ return texture.texture.wasLoadingPerfect(); } ) 
		&& std::all_of(blackSquares.cbegin(), blackSquares.cend(), [](auto &texture){ return texture.texture.wasLoadingPerfect(); } );
}

void InfoBar::drawBricksTextures(sdl2::RendererWindow& rndWnd)
{
	for( int i{0} ; i < GameScreenWidth / brickTexture.sprite.width() ; ++i )
	{
		brickTexture.draw(rndWnd, i * brickTexture.sprite.width(), 0);
	}
}

void InfoBar::drawAllTexts(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &text : barTexts )
	{
		text.draw(rndWnd);
	}
}

void InfoBar::drawAllBlackSquares(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &square : blackSquares )
	{
		square.draw(rndWnd);
	}
}

void InfoBar::drawData(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &text : dataTexts )
	{
		text.draw(rndWnd);
	}
}

void InfoBar::updateText(Essentials& essentials, unsigned inputValue, std::size_t index, const SDL_Color& col, const Offset& position)
{
	assert( index < infoBarTexts::Max );
	if( isGraphicalTextUpdateNeeded[index] )
	{
		dataTexts[index].texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, std::to_string(inputValue), col);
		dataTexts[index].resetSpritePosition( TexturePosition{position, false, true} );
		isGraphicalTextUpdateNeeded[index] = false;
	}
}

void InfoBar::updateText(Essentials& essentials, double inputValue, std::size_t index, const SDL_Color& col, const Offset& position)
{
	assert( index < infoBarTexts::Max );
	if( isGraphicalTextUpdateNeeded[index] )
	{
		dataTexts[index].texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, std::to_string(inputValue), col);
		dataTexts[index].resetSpritePosition(TexturePosition{position, false, true} );
		isGraphicalTextUpdateNeeded[index] = false;
	}
}