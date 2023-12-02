#include "appStart/miniScreenGui.h"
#include "logging/logsStruct.h"
#include "texts/textLoader.h"
#include "texturing/texturePosition.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"
#include "appStart/miniScreenConsts.h"
#include <algorithm>

constexpr unsigned MiniScreenFontSize = 20;

MiniScreen::MiniScreen(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const TextsBlocks& texts, int squareSize, int screenWidth, int screenHeight):
	fancyFont{ logs.error, FancyFontPath, MiniScreenFontSize },
	bricksBackground{ logs, rndWnd, "textures/wallpapers/miniScreenBg.png", TexturePosition{ 0, 0, false, false } }
{
	loadTextsTextures(logs, rndWnd, texts, screenWidth, screenHeight);
	setTexturesCoordinates(squareSize);
}

MiniScreen::operator bool() const
{
	return fancyFont && std::all_of( std::cbegin(textsTextures), std::cend(textsTextures), [](auto const &combo){ 
										if( combo.texture )
											return true;
										else 
											return false; } ) && bricksBackground.texture;
}

void MiniScreen::drawAll(sdl2::RendererWindow& rndWnd) const
{
	bricksBackground.draw(rndWnd);
	drawTextsTextures(rndWnd);
}

void MiniScreen::loadTextsTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const TextsBlocks& texts, int screenWidth, int screenHeight)
{
	if( fancyFont && texts.size() == miniScreenTexts::Max )
	{
		for( std::size_t i{0} ; i < texts.size() ; ++i )
		{
			if( i != miniScreenTexts::F5_WindowedMode )
			{
				textsTextures.emplace_back( TextureCombo{logs, rndWnd, fancyFont, texts[i], WhiteColor, TexturePosition{} } );
			}
			else{
				textsTextures.emplace_back( TextureCombo{logs, rndWnd, fancyFont, texts[i] + " (" + std::to_string(screenWidth) + " x " + std::to_string(screenHeight) + ") ", 
											WhiteColor, TexturePosition{} } );
			}
		}
	}
	else{
		logs.error << "Error: either the font or the texts that should be loaded for the mini screen were not.\n";
	}
}

void MiniScreen::setTexturesCoordinates(int squareSize)
{
	textsTextures[miniScreenTexts::F1_FullScreen].resetSpritePosition( TexturePosition{ squareSize, squareSize, false, true} );
	textsTextures[miniScreenTexts::F5_WindowedMode].resetSpritePosition( TexturePosition{ squareSize, squareSize*3, false, true} );
	textsTextures[miniScreenTexts::WarningBetaVersion].resetSpritePosition( TexturePosition{ squareSize, squareSize*4, false, true} );
	textsTextures[miniScreenTexts::PressEscapeToGoBack].resetSpritePosition( TexturePosition{ squareSize / 4, squareSize * 5 + squareSize / 2, false, true } );
	textsTextures[miniScreenTexts::ToThePreviousMenu].resetSpritePosition( TexturePosition{ squareSize / 4, squareSize * 6, false, true } );
}

void MiniScreen::drawTextsTextures(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &txt : textsTextures )
	{
		txt.draw(rndWnd);
	}
}
