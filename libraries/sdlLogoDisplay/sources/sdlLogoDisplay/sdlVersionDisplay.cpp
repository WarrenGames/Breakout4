#include "sdlLogoDisplay/sdlVersionDisplay.h"
#include "texturing/texturePosition.h"
#include "texturing/rendererWindow.h"
#include "texts/textLoader.h"
#include "logging/logsStruct.h"
#include "versioning/makeStringFromVersion.h"
#include "consts/fontsPaths.h"

enum{
	VersionNumber,
	VersionMax
};

constexpr SDL_Color SdlVersionTextColor = { 0, 0, 0, 255 };

SDL_VersionDisplay::SDL_VersionDisplay(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const fs::path& languageFilePath, int fontSize, int squareSize):
	arialFont{ logs.error, ArialFontPath, fontSize},
	isLoadingPerfect{ true }
{
	if( const TextsBlocks languagesTexts{logs.error, languageFilePath, VersionMax } )
	{
		SDL_VERSION(&sdlVersion);
		textTexture.texture.loadBlendedText(logs, rndWnd, arialFont, languagesTexts[0] + sdl2::getVersionNumber(sdlVersion), SdlVersionTextColor);
			
		if( textTexture.texture )
		{
			textTexture.resetSpritePosition( TexturePosition{ rndWnd.width() / 2, rndWnd.height() - squareSize / 2 } );
			textTexture.sprite.setXPos( rndWnd.width() - squareSize - textTexture.sprite.width() );
		}
		else{
			isLoadingPerfect = false;
		}
	}
	else{
		isLoadingPerfect = false;
	}
}

void SDL_VersionDisplay::drawVersion(sdl2::RendererWindow& rndWnd) const
{
	if( isLoadingPerfect )
	{
		textTexture.draw(rndWnd);
	}
}