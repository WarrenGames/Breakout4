#include "contexts/onePlayerGame/newGame/newGameInterface.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"

onePlGame::newGame::Interface::Interface(Essentials& essentials):
	fancyFont{essentials.logs.error, FancyFontPath, FontBigPointSize},
	languageTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::OnePlayerNewGame), onePlGame::newGame::TextSkillMax},
	screenTitle{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::newGame::TextTitle], WhiteColor, TexturePosition{GameScreenWidth/2, SQR_SIZE, true, true} },
	screenBackground{essentials.logs, essentials.rndWnd, "textures/wallpapers/onePlayerMainMenu.png", TexturePosition{ 0, 0, false, false } },
	newGameButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::newGame::TextStartNewGame], GreenColor, WhiteColor, GameScreenWidth / 2, SQR_SIZE * 4, true},
	loadASavedGame{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::newGame::TextLoadSavedGame], GreenColor, WhiteColor, GameScreenWidth / 2, SQR_SIZE * 6, true},
	seeDoneScores{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::newGame::TextSeeDoneScores], GreenColor, WhiteColor, GameScreenWidth / 2, SQR_SIZE * 8, true},
	recordDemo{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::newGame::RecordA_Demo], GreenColor, WhiteColor, GameScreenWidth / 2, SQR_SIZE * 10, true },
	playDemo{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::newGame::PlayDemo], GreenColor, WhiteColor, GameScreenWidth / 2, SQR_SIZE * 12, true },
	goBackButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::newGame::TextGoBack], GreenColor, WhiteColor, GameScreenWidth / 2, SQR_SIZE * 14, true},
	bricksAnimation{essentials.logs, essentials.rndWnd,onePlGame::newGame::BrickImagesNumber, "textures/gameGUI/animations/+10brick/brick10Anim_"},
	bricksSprites{bricksAnimation},
	animIndexes{ 0, 0, 0 }
{
	setIndexesAtInitialization();
}

void onePlGame::newGame::Interface::update(const Essentials& essentials)
{
	newGameButton.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	loadASavedGame.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	seeDoneScores.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	recordDemo.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	playDemo.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	goBackButton.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	updateAnimation();
}

void onePlGame::newGame::Interface::drawEverything(Essentials& essentials)
{
	screenBackground.draw(essentials.rndWnd);
	screenTitle.draw(essentials.rndWnd);
	newGameButton.drawButton(essentials.rndWnd);
	loadASavedGame.drawButton(essentials.rndWnd);
	seeDoneScores.drawButton(essentials.rndWnd);
	recordDemo.drawButton(essentials.rndWnd);
	playDemo.drawButton(essentials.rndWnd);
	goBackButton.drawButton(essentials.rndWnd);
	bricksSprites.draw(essentials.rndWnd, Offset{ SQR_SIZE * 2, SQR_SIZE * 4}, animIndexes[0] );
	bricksSprites.draw(essentials.rndWnd, Offset{ SQR_SIZE * 1, SQR_SIZE * 12}, animIndexes[1] );
	bricksSprites.draw(essentials.rndWnd, Offset{ SQR_SIZE * 16, SQR_SIZE * 8}, animIndexes[2] );
}

void onePlGame::newGame::Interface::updateAnimation()
{
	if( animDelay.hasTimeElapsed( std::chrono::milliseconds{60} ) )
	{
		animDelay.joinTimePoints();
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
	}
}

void onePlGame::newGame::Interface::setIndexesAtInitialization()
{
	if( bricksAnimation.wasLoadingPerfect() )
	{
		animIndexes[0] = 0;
		animIndexes[1] = static_cast<int>( bricksAnimation.size() ) / 3;
		animIndexes[2] = static_cast<int>( bricksAnimation.size() ) * 2 / 3;
	}
}