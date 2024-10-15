#include "levelComponents/rims/rimsScoreValueDrawing.h"
#include "levelComponents/rims/rimsScoreStock.h"
#include "types/essentialsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "texturing/texturePosition.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"
#include "consts/rimsConsts.h"
#include <cassert>

RimsScoreValueDrawing::RimsScoreValueDrawing(Essentials& essentials, const RimsScoreStock& scoresValues):
	texts{ essentials.logs.error, path::getLanguageFile(essentials.language, file::OnePlayerRimsPointsAdd), rims::PointsRowMax },
	font{ essentials.logs.error, FancyFontPath, FontMediumPointSize },
	isLoadingPerfect{ true }
{
	assert( scoresValues.size() == rims::PointsRowMax );
	if( ! texts )
	{
		isLoadingPerfect = false;
	}
	loadTextures(essentials, scoresValues);
}

void RimsScoreValueDrawing::drawText(Essentials& essentials, std::size_t index) const
{
	assert( index < pointsTexture.size() );
	pointsTexture[index].draw(essentials.rndWnd);
}

void RimsScoreValueDrawing::loadTextures(Essentials& essentials, const RimsScoreStock& scoresValues)
{
	if( font )
	{
		assert( scoresValues.size() == texts.size() );
		
		for( std::size_t i{0} ; i < scoresValues.size() && i < texts.size() ; ++i )
		{
			pointsTexture.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, font, std::to_string(scoresValues.getGivenRimScore(i) ) + texts[i], WhiteColor,
													TexturePosition{ GameScreenWidth / 2, GameScreenHeight - SQR_SIZE * 2 - SQR_SIZE / 2, true, true } } );
		}
	}
	else{
		isLoadingPerfect = false;
	}
}