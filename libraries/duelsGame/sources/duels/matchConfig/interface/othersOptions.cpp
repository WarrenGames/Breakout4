#include "duels/matchConfig/interface/othersOptions.h"
#include "logging/logsStruct.h"
#include "texturing/texturePosition.h"
#include "duels/inGameObjects/gameElements/duelsLevelOptions.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"

constexpr int BoxWidth = SQR_SIZE;
constexpr int BoxHeight = SQR_SIZE / 2;

duels::OtherOptions::OtherOptions(AppLogFiles& logs, const std::string& chosenLanguage, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, duels::LevelOptions& levelOptions):
	langTexts{logs.error, path::getLanguageFile(chosenLanguage, file::DuelsOtherOptions), duels::OtherOptionsMax}
{
	createTextsData(logs, rndWnd, fancyFont);
	createEditBoxes(logs, rndWnd, levelOptions);
}

void duels::OtherOptions::catchUserFocus(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Offset& mousePos, bool mouseButton)
{
	for( auto &box : editBoxes )
		box.catchUserFocus(logs, rndWnd, mousePos, mouseButton);
}

void duels::OtherOptions::drawEverything(sdl2::RendererWindow& rndWnd) const
{
	drawBoxes(rndWnd);
	drawTexts(rndWnd);
}

void duels::OtherOptions::drawBoxes(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &box : editBoxes )
		box.drawBoxWithoutFocus(rndWnd);
}

void duels::OtherOptions::drawTexts(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &text : texts )
		text.draw(rndWnd);
}

void duels::OtherOptions::createTextsData(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont)
{
	for( std::size_t i{0} ; i < langTexts.size() ; ++i )
	{
		texts.emplace_back( TextureCombo{logs, rndWnd, fancyFont, langTexts[i], WhiteColor, TexturePosition{SQR_SIZE*8, SQR_SIZE*(2 + static_cast<int>(i) )+ SQR_SIZE/4, false, true} } );
	}
}

void duels::OtherOptions::createEditBoxes(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, duels::LevelOptions& levelOptions)
{
	editBoxes.emplace_back( UintEditBox{logs, rndWnd, {GameScreenWidth - SQR_SIZE*2, SQR_SIZE*2, BoxWidth, BoxHeight}, FontSmallPointSize, levelOptions.pointsToPlayInZone} );
	editBoxes.emplace_back( UintEditBox{logs, rndWnd, {GameScreenWidth - SQR_SIZE*2, SQR_SIZE*3, BoxWidth, BoxHeight}, FontSmallPointSize, levelOptions.secondsBeforeNewCoin} );
	editBoxes.emplace_back( UintEditBox{logs, rndWnd, {GameScreenWidth - SQR_SIZE*2, SQR_SIZE*4, BoxWidth, BoxHeight}, FontSmallPointSize, levelOptions.coinsMax} );
	editBoxes.emplace_back( UintEditBox{logs, rndWnd, {GameScreenWidth - SQR_SIZE*2, SQR_SIZE*5, BoxWidth, BoxHeight}, FontSmallPointSize, levelOptions.secondsBeforeNewBall} );
	editBoxes.emplace_back( UintEditBox{logs, rndWnd, {GameScreenWidth - SQR_SIZE*2, SQR_SIZE*6, BoxWidth, BoxHeight}, FontSmallPointSize, levelOptions.ballsMax} );
}
