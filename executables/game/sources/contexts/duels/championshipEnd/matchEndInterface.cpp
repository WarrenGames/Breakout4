#include "contexts/duels/championshipEnd/matchEndInterface.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "contexts/duels/inGameObjects/gameElements/duelsTypes.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"

enum{ DuelMatchEndBluePlayer, DuelMatchEndRedPlayer, DuelMatchEndWins, DuelMatchEndLose, DuelMatchEndNoWinner, DuelMatchEndMax };

DuelsEndInterface::DuelsEndInterface(Essentials& essentials, const duels::LevelOptions& levelOptions):
	fancyFont{essentials.logs.error, FancyFontPath, FontMediumPointSize},
	texts{essentials.logs.error, path::getLanguageFile(essentials.language, file::DUELS_MATCH_END), DuelMatchEndMax},
	noWinner{essentials.logs, essentials.rndWnd, fancyFont, texts[DuelMatchEndNoWinner], WhiteColor, TexturePosition{ Offset{GameScreenWidth / 2, GameScreenHeight / 2}, true, true} }
{
	
	TexturePosition topPos{Offset{GameScreenWidth / 2, GameScreenHeight / 2 - SQR_SIZE * 2}, true, true};
	TexturePosition bottomPos{Offset{GameScreenWidth / 2, GameScreenHeight / 2 + SQR_SIZE * 2}, true, true};
	
	if( levelOptions.playersScores[duels::PlayerBlue] > levelOptions.playersScores[duels::PlayerRed] )
	{
		winnerIs.texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, texts[DuelMatchEndBluePlayer] + texts[DuelMatchEndWins], BlueColor);
		winnerIs.resetSpritePosition(bottomPos);
		
		chocolateMedal.texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, texts[DuelMatchEndRedPlayer] + texts[DuelMatchEndLose], RedColor);
		chocolateMedal.resetSpritePosition(topPos);
	}
	else if( levelOptions.playersScores[duels::PlayerBlue] < levelOptions.playersScores[duels::PlayerRed] )
	{
		winnerIs.texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, texts[DuelMatchEndRedPlayer] + texts[DuelMatchEndWins], RedColor);
		winnerIs.resetSpritePosition(topPos);
		
		chocolateMedal.texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, texts[DuelMatchEndBluePlayer] + texts[DuelMatchEndLose], BlueColor);
		chocolateMedal.resetSpritePosition(bottomPos);
	}
}

void DuelsEndInterface::drawEverything(Essentials& essentials, const duels::LevelOptions& levelOptions) const
{
	if( levelOptions.playersScores[duels::PlayerBlue] == levelOptions.playersScores[duels::PlayerRed] )
	{
		noWinner.draw(essentials.rndWnd);
	}
	else{
		winnerIs.draw(essentials.rndWnd);
		chocolateMedal.draw(essentials.rndWnd);
	}
}