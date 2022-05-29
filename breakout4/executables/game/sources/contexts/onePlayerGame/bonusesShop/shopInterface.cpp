#include "contexts/onePlayerGame/bonusesShop/shopInterface.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "crossLevel/playerData.h"
#include "advancedDrawing/interfaceGeneratorLanguage/elementsLoadingFunctions/texturesComponent.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/onePlayerBonusesConsts.h"

constexpr int TEXTS_X_CENTER_POS = GAME_SCREEN_WIDTH / 2;
constexpr int TEXTS_Y_CENTER_POS = GAME_SCREEN_HEIGHT - SQR_SIZE;

constexpr char SHOP_BAG_ICONS_SCRIPT_FILE[] = "data/interfaceScripts/onePlayerShopBagIcons.txt";

onePlayerShop::ShopInterface::ShopInterface(Essentials& essentials, const PlayerData& playerData):
	bonusesTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::ONE_PLAY_BAG_BONUS), onePlGame::BONUS_MAX},
	fancyFont{essentials.logs.error, FANCYFONTPATH, FONT_BIG_PTSIZE},
	backgroundWallpaper{essentials.logs, essentials.rndWnd, "textures/wallpapers/jarsShelf.png"},
	bonusesCount{essentials},
	coinTextures{essentials.logs, essentials.rndWnd, "data/textures/coinTexturesList.txt"},
	coinSprites{coinTextures},
	coinSample{ Offset{GAME_SCREEN_WIDTH - SQR_SIZE*3 - SQR_SIZE / 2, GAME_SCREEN_HEIGHT - SQR_SIZE - SQR_SIZE / 2} }
{
	igl::texture::openScriptFileWithImageOnly(essentials.logs, essentials.rndWnd, bagIcons, SHOP_BAG_ICONS_SCRIPT_FILE, SQR_SIZE);
	bonusesCount.updateNeededTexts(essentials, playerData, bagIcons);
	if( bonusesTexts && fancyFont )
	{
		updateCoinNumberText(essentials, playerData);
		for( auto const &text : bonusesTexts )
		{
			texts.emplace_back(TextureCombo{essentials.logs, essentials.rndWnd, fancyFont, text, YELLOW_COL, TexturePosition{TEXTS_X_CENTER_POS, TEXTS_Y_CENTER_POS, true, true} } );
		}
	}
	else{
		
	}
}

void onePlayerShop::ShopInterface::update()
{
	animateCoins();
}

void onePlayerShop::ShopInterface::animateCoins()
{
	if( coinAnimDelay.hasTimeElapsed( std::chrono::milliseconds{50} ) )
	{
		coinSample.incrementAnimIndex();
		coinAnimDelay.joinTimePoints();
	}
}

void onePlayerShop::ShopInterface::updateCoinNumberText(Essentials& essentials, const PlayerData& playerData)
{
	coinNumberText.texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, " = " + std::to_string(playerData.bonusCoinsNumber), YELLOW_COL);
	coinNumberText.resetSpritePosition(	TexturePosition{GAME_SCREEN_WIDTH- SQR_SIZE*2, GAME_SCREEN_HEIGHT-SQR_SIZE, true, true} );
}

void onePlayerShop::ShopInterface::drawAdequateText(Essentials& essentials, unsigned selection) const
{
	if( selection < texts.size() )
	{
		texts[selection].draw(essentials.rndWnd);
	}
}

void onePlayerShop::ShopInterface::drawBagIcons(Essentials& essentials) const
{
	for( auto const &icon : bagIcons )
	{
		icon.draw(essentials.rndWnd);
	}
}

void onePlayerShop::ShopInterface::drawEverything(Essentials& essentials, unsigned selection)
{
	backgroundWallpaper.draw(essentials.rndWnd);
	drawAdequateText(essentials, selection);
	drawBagIcons(essentials);
	bonusesCount.drawEverything(essentials);
	coinSprites.draw(essentials.rndWnd, coinSample.pos, coinSample.animationIndex);
	coinNumberText.draw(essentials.rndWnd);
}