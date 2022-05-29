#include "contexts/onePlayerGame/levelComponents/inGameBagThings/bagObject.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "advancedDrawing/interfaceGeneratorLanguage/elementsLoadingFunctions/texturesComponent.h"
#include "consts/constexprScreen.h"

constexpr char GAME_BAG_ICONS_SCRIPT_FILE[] = "data/interfaceScripts/onePlayerGameBagIcons.txt";
constexpr int ICONS_Y_POS = 640;

PlayerBag::PlayerBag(Essentials& essentials, const PlayerData& playerData):
	bonusesCount{essentials},
	selectedBonus{onePlGame::BONUS_STICKY},
	selectionRect{getSquareXCoord(), ICONS_Y_POS, SQR_SIZE*2, SQR_SIZE*2 + SQR_SIZE / 2},
	quitBagView{false}
{
	igl::texture::openScriptFileWithImageOnly(essentials.logs, essentials.rndWnd, bagIcons, GAME_BAG_ICONS_SCRIPT_FILE, SQR_SIZE);
	bonusesCount.updateNeededTexts(essentials, playerData, bagIcons);
}

int PlayerBag::getSquareXCoord()
{
	return selectedBonus * 3 * SQR_SIZE + SQR_SIZE * 2;
}

void PlayerBag::selectForward()
{
	if( selectedBonus + 1 < onePlGame::BONUS_MAX )
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
		selectedBonus = onePlGame::BONUS_MAX - 1;
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