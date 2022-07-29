#include "contexts/duels/championshipEnd/matchEndInterface.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "contexts/duels/inGameObjects/gameElements/duelsTypes.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"

enum{ DUEL_MATCH_END_BLUE_PLAYER, DUEL_MATCH_END_RED_PLAYER, DUEL_MATCH_END_WINS, DUEL_MATCH_END_LOSE, DUEL_MATCH_END_NO_WINNER, DUEL_MATCH_END_MAX };

DuelsEndInterface::DuelsEndInterface(Essentials& essentials, const duels::LevelOptions& levelOptions):
	fancyFont{essentials.logs.error, FANCYFONTPATH, FONT_MEDIUM_PTSIZE},
	texts{essentials.logs.error, path::getLanguageFile(essentials.language, file::DUELS_MATCH_END), DUEL_MATCH_END_MAX},
	noWinner{essentials.logs, essentials.rndWnd, fancyFont, texts[DUEL_MATCH_END_NO_WINNER], WHITE_COL, TexturePosition{ Offset{GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2}, true, true} }
{
	
	TexturePosition topPos{Offset{GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2 - SQR_SIZE * 2}, true, true};
	TexturePosition bottomPos{Offset{GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2 + SQR_SIZE * 2}, true, true};
	
	if( levelOptions.playersScores[duels::PLAYER_BLUE] > levelOptions.playersScores[duels::PLAYER_RED] )
	{
		winnerIs.texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, texts[DUEL_MATCH_END_BLUE_PLAYER] + texts[DUEL_MATCH_END_WINS], BLUE_COL);
		winnerIs.resetSpritePosition(bottomPos);
		
		chocolateMedal.texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, texts[DUEL_MATCH_END_RED_PLAYER] + texts[DUEL_MATCH_END_LOSE], RED_COL);
		chocolateMedal.resetSpritePosition(topPos);
	}
	else if( levelOptions.playersScores[duels::PLAYER_BLUE] < levelOptions.playersScores[duels::PLAYER_RED] )
	{
		winnerIs.texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, texts[DUEL_MATCH_END_RED_PLAYER] + texts[DUEL_MATCH_END_WINS], RED_COL);
		winnerIs.resetSpritePosition(topPos);
		
		chocolateMedal.texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, texts[DUEL_MATCH_END_BLUE_PLAYER] + texts[DUEL_MATCH_END_LOSE], BLUE_COL);
		chocolateMedal.resetSpritePosition(bottomPos);
	}
}

void DuelsEndInterface::drawEverything(Essentials& essentials, const duels::LevelOptions& levelOptions) const
{
	if( levelOptions.playersScores[duels::PLAYER_BLUE] == levelOptions.playersScores[duels::PLAYER_RED] )
	{
		noWinner.draw(essentials.rndWnd);
	}
	else{
		winnerIs.draw(essentials.rndWnd);
		chocolateMedal.draw(essentials.rndWnd);
	}
}