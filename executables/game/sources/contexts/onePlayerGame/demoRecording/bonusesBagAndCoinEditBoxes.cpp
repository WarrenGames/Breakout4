#include "contexts/onePlayerGame/demoRecording/bonusesBagAndCoinEditBoxes.h"
#include "crossLevel/playerData.h"
#include "types/essentialsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "texturing/texturePosition.h"
#include "consts/onePlayerBonusesConsts.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"

constexpr char BonusesLanguageFile[] = "1player_bagBonusesList.txt";

constexpr int BoxWidth = SQR_SIZE + SQR_SIZE / 2;
constexpr int BoxHeight = SQR_SIZE / 2;

onePlGame::demoRecording::BonusesAndCoinsEdition::BonusesAndCoinsEdition(Essentials& essentials, PlayerData& playerData):
	languagesTexts{essentials.logs.error, path::getLanguageFile(essentials.language, BonusesLanguageFile), onePlGame::demoRecording::BonusMax },
	arial{ essentials.logs.error, ArialFontPath, FontMediumPointSize},
	coinsText{ essentials.logs, essentials.rndWnd, arial, languagesTexts[onePlGame::demoRecording::BonusCoinNumber], WhiteColor, TexturePosition{ SQR_SIZE, SQR_SIZE * 2, false, true} },
	coinsNumberBox{ essentials.logs, essentials.rndWnd, SDL_Rect{ SQR_SIZE *7, SQR_SIZE * 2 - BoxHeight / 2, BoxWidth, BoxHeight }, FontMediumPointSize, playerData.bonusCoinsNumber }

{
	createBonusesTexts(essentials);
	createBonusesBoxes(essentials, playerData);
}

void onePlGame::demoRecording::BonusesAndCoinsEdition::drawEverything(Essentials& essentials) const
{
	coinsNumberBox.drawBoxWithoutFocus(essentials.rndWnd);
	drawBonusesBoxes(essentials);
	drawBonusesHelpTexts(essentials);
	coinsText.draw(essentials.rndWnd);
}

void onePlGame::demoRecording::BonusesAndCoinsEdition::updateBoxesEvents(Essentials& essentials)
{
	updateBonusesBoxesEvents(essentials);
	coinsNumberBox.catchUserFocus(essentials.logs, essentials.rndWnd, essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
}

void onePlGame::demoRecording::BonusesAndCoinsEdition::createBonusesTexts(Essentials& essentials)
{
	for( std::size_t i{0} ; i < onePlGame::BonusMax ; ++i )
	{
		bonusesHelpTexts.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, arial, languagesTexts[i], WhiteColor, 
										TexturePosition{SQR_SIZE, SQR_SIZE*4 + SQR_SIZE * static_cast<int>(i), false, true} } );
	}
}

void onePlGame::demoRecording::BonusesAndCoinsEdition::createBonusesBoxes(Essentials& essentials, PlayerData& playerData)
{
	for( std::size_t i{0} ; i < onePlGame::BonusMax ; ++i )
	{
		bagBonusesBoxes.emplace_back( UintEditBox{essentials.logs, essentials.rndWnd, 
						SDL_Rect{SQR_SIZE*7, SQR_SIZE*4 + SQR_SIZE * static_cast<int>(i) - BoxHeight / 2, BoxWidth, BoxHeight}, FontMediumPointSize, playerData.bonusesInBag[i] } );
	}
}

void onePlGame::demoRecording::BonusesAndCoinsEdition::drawBonusesHelpTexts(Essentials& essentials) const
{
	for( auto const &txt : bonusesHelpTexts )
	{
		txt.draw(essentials.rndWnd);
	}
}

void onePlGame::demoRecording::BonusesAndCoinsEdition::drawBonusesBoxes(Essentials& essentials) const
{
	for( auto const &box : bagBonusesBoxes )
	{
		box.drawBoxWithoutFocus(essentials.rndWnd);
	}
}

void onePlGame::demoRecording::BonusesAndCoinsEdition::updateBonusesBoxesEvents(Essentials& essentials)
{
	for( auto &box : bagBonusesBoxes )
	{
		box.catchUserFocus(essentials.logs, essentials.rndWnd, essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	}
}