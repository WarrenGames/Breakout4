#include "levelComponents/inGameBagThings/bagObject.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "advancedDrawing/interfaceGeneratorLanguage/elementsLoadingFunctions/texturesComponent.h"
#include "consts/constexprScreen.h"
#include "consts/onePlayerBonusesConsts.h"

constexpr char GameBagIconsScriptFile[] = "data/interfaceScripts/onePlayerGameBagIcons.txt";
constexpr int IconsY_Position = 640 * SQR_SIZE / 64;

PlayerBag::PlayerBag(Essentials& essentials, const PlayerData& playerData):
	bonusesCount{essentials},
	selectedBonus{onePlGame::BonusStickyRacket},
	selectionRect{getSquareXCoord(), IconsY_Position, SQR_SIZE*2, SQR_SIZE*2 + SQR_SIZE / 2},
	quitBagView{false}
{
	igl::texture::openScriptFileWithImageOnly(essentials.logs, essentials.rndWnd, bagIcons, GameBagIconsScriptFile, SQR_SIZE);
	bonusesCount.updateNeededTexts(essentials, playerData, bagIcons);
}

int PlayerBag::getSquareXCoord()
{
	return selectedBonus * 3 * SQR_SIZE + SQR_SIZE * 2;
}

void PlayerBag::selectForward()
{
	if( selectedBonus + 1 < onePlGame::BonusMax )
	{
		++selectedBonus;
	}
	else{
		selectedBonus = 0;
	}
	selectionRect.x = getSquareXCoord();
}

void PlayerBag::selectBackward()
{
	if( selectedBonus > 0 )
	{
		--selectedBonus;
	}
	else{
		selectedBonus = onePlGame::BonusMax - 1;
	}
	selectionRect.x = getSquareXCoord();
}

void PlayerBag::drawBagIcons(Essentials& essentials) const
{
	for( auto const &icon : bagIcons )
	{
		icon.draw(essentials.rndWnd);
	}
}

void PlayerBag::drawEverything(Essentials& essentials) const
{
	drawBagIcons(essentials);
	bonusesCount.drawEverything(essentials);
}