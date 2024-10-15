#include "duels/matchConfig/textFilesLoading/fromStringsToTextures.h"
#include "logging/logsStruct.h"
#include "texturing/texturePosition.h"
#include "texts/textLoader.h"
#include "texturing/texturesCombo.h"
#include "texturing/rendererWindow.h"
#include "text/sdl2ttf_font.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"

void createZoneChoiceTextsTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const TextsBlocks& texts, std::vector< TextureCombo >& textures, int fontSize)
{
	const sdl2::Font arialFont{logs.error, ArialFontPath, fontSize};
	
	if( arialFont )
	{
		for( std::size_t i{0} ; i < texts.size() ; ++i )
		{
			textures.emplace_back(TextureCombo{logs, rndWnd, arialFont, texts[i], BlackColor, 
								TexturePosition{SQR_SIZE / 2, GameScreenHeight-SQR_SIZE, false, true } });
		}
	}
}