#include "contexts/onePlayerGame/newGame/newGameInterface.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"

onePlGame::newGame::Interface::Interface(Essentials& essentials):
	fancyFont{essentials.logs.error, FANCYFONTPATH, FONT_BIG_PTSIZE},
	languageTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::ONE_PLAY_NEW_GAME), onePlGame::newGame::TXT_MAX},
	screenTitle{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::newGame::TXT_TITLE], WHITE_COL, TexturePosition{GAME_SCREEN_WIDTH/2, SQR_SIZE, true, true} },
	newGameButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::newGame::TXT_START_NEW_GAME], GREEN_COL, WHITE_COL, GAME_SCREEN_WIDTH / 2, SQR_SIZE * 5, true},
	loadASavedGame{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::newGame::TXT_LOAD_A_SAVED_GAME], GREEN_COL, WHITE_COL, GAME_SCREEN_WIDTH / 2, SQR_SIZE * 7, true},
	seeDoneScores{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::newGame::TXT_SEE_DONE_SCORES], GREEN_COL, WHITE_COL, GAME_SCREEN_WIDTH / 2, SQR_SIZE * 9, true},
	goBackButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::newGame::TXT_GO_BACK], GREEN_COL, WHITE_COL, GAME_SCREEN_WIDTH / 2, SQR_SIZE * 12, true},
	bricksAnimation{essentials.logs, essentials.rndWnd,onePlGame::newGame::BRICK_IMG_NUM, "textures/gameGUI/animations/+10brick/brick10Anim_"},
	bricksSprites{bricksAnimation},
	animIndexes{ 0, 0, 0 }
{
	
}

void onePlGame::newGame::Interface::update(const Essentials& essentials)
{
	newGameButton.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	loadASavedGame.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	seeDoneScores.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	goBackButton.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	updateAnimation();
}

void onePlGame::newGame::Interface::drawEverything(Essentials& essentials)
{
	screenTitle.draw(essentials.rndWnd);
	newGameButton.drawButton(essentials.rndWnd);
	loadASavedGame.drawButton(essentials.rndWnd);
	seeDoneScores.drawButton(essentials.rndWnd);
	goBackButton.drawButton(essentials.rndWnd);
	bricksSprites.draw(essentials.rndWnd, Offset{ SQR_SIZE * 2, SQR_SIZE * 4}, animIndexes[0] );
	bricksSprites.draw(essentials.rndWnd, Offset{ SQR_SIZE * 1, SQR_SIZE * 12}, animIndexes[1] );
	bricksSprites.draw(essentials.rndWnd, Offset{ SQR_SIZE * 16, SQR_SIZE * 8}, animIndexes[2] );
}

void onePlGame::newGame::Interface::updateAnimation()
{
	if( animDelay.hasTimeElapsed( std::chrono::milliseconds{60} ) )
	{
		for( auto &index : animIndexes )
		{
			if( index + 1 < bricksAnimation.size() )
			{
				index++;
			}
			else{
				index = 0;
			}
		}
		animDelay.joinTimePoints();
	}
}