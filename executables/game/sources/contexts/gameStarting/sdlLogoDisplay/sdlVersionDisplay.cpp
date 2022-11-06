#include "contexts/gameStarting/sdlLogoDisplay/sdlVersionDisplay.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "texts/textLoader.h"
#include "versioning/makeStringFromVersion.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "consts/fontsConsts.h"

constexpr char VersionFilePath[] = "versioning/sdlVersion.txt";

enum{
	VersionNumber,
	VersionMax
};

constexpr SDL_Color TextColor = { 255, 0, 0, 255 };

SDL_VersionDisplay::SDL_VersionDisplay(Essentials& essentials):
	arialFont{ essentials.logs.error, ArialFontPath, FontMediumPointSize},
	isLoadingPerfect{ true }
{
	if( const TextsBlocks languagesTexts{essentials.logs.error, path::getLanguageFile(essentials.language, VersionFilePath), VersionMax } )
	{
		SDL_VERSION(&sdlVersion);
		textTexture.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arialFont, 
											languagesTexts[0] + sdl2::getVersionNumber(sdlVersion), TextColor);
			
		if( textTexture.texture )
		{
			textTexture.resetSpritePosition( TexturePosition{ GameScreenWidth / 2, GameScreenHeight - SQR_SIZE / 2 } );
			textTexture.sprite.setXPos( GameScreenWidth - SQR_SIZE - textTexture.sprite.width() );
		}
		else{
			isLoadingPerfect = false;
		}
	}
	else{
		isLoadingPerfect = false;
	}
}

void SDL_VersionDisplay::drawVersion(Essentials& essentials) const
{
	if( isLoadingPerfect )
	{
		textTexture.draw(essentials.rndWnd);
	}
}