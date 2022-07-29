#include "contexts/gameStarting/sdlLogoDisplay/sdlVersionDisplay.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "texts/textLoader.h"
#include "versioning/makeStringFromVersion.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "consts/fontsConsts.h"

constexpr char VERSION_FILE_PATH[] = "versioning/sdlVersion.txt";

enum{
	VERSION_NUMBER,
	VERSION_MAX
};

constexpr SDL_Color TEXT_COLOR = { 255, 0, 0, 255 };

SDL_VersionDisplay::SDL_VersionDisplay(Essentials& essentials):
	arialFont{ essentials.logs.error, ARIALFONTPATH, FONT_MEDIUM_PTSIZE},
	isLoadingPerfect{ true }
{
	if( const TextsBlocks languagesTexts{essentials.logs.error, path::getLanguageFile(essentials.language, VERSION_FILE_PATH), VERSION_MAX } )
	{
		SDL_VERSION(&sdlVersion);
		textTexture.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arialFont, 
											languagesTexts[0] + sdl2::getVersionNumber(sdlVersion), TEXT_COLOR);
			
		if( textTexture.texture )
		{
			textTexture.resetSpritePosition( TexturePosition{ GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT - SQR_SIZE / 2 } );
			textTexture.sprite.setXPos( GAME_SCREEN_WIDTH - SQR_SIZE - textTexture.sprite.width() );
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