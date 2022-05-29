#ifndef ONE_PLAYER_SHOP_INTERFACE_H
#define ONE_PLAYER_SHOP_INTERFACE_H

#include "texts/textLoader.h"
#include "text/sdl2ttf_font.h"
#include "consts/fontsConsts.h"
#include "advancedDrawing/texturesLoading/fileTexturesList.h"
#include "advancedDrawing/texturesDrawing/constAnimationDrawing.h"
#include "contexts/onePlayerGame/levelComponents/inGameBagThings/bonusesCountGraphics.h"
#include "contexts/onePlayerGame/levelComponents/bonusCoins/coinSample.h"
#include "time/accurateTime.h"
#include <vector>

struct Essentials;
struct PlayerData;

namespace onePlayerShop{

struct ShopInterface
{
	const TextsBlocks bonusesTexts;
	const sdl2::Font fancyFont;
	const TextureCombo backgroundWallpaper;
	std::vector< TextureCombo > texts;
	std::vector< TextureCombo > bagIcons;
	BonusesCountGraphics bonusesCount;
	TexturesFilesList coinTextures;
	ConstAnimDraw coinSprites;
	AccurateTimeDelay coinAnimDelay;
	CoinSample coinSample;
	TextureCombo coinNumberText;
	
	explicit ShopInterface(Essentials& essentials, const PlayerData& playerData);
	~ShopInterface() = default;
	ShopInterface( const ShopInterface& ) = delete;
	ShopInterface& operator= ( const ShopInterface& ) = delete;
	ShopInterface( ShopInterface&& ) = default;
	ShopInterface& operator= ( ShopInterface&& ) = default;
	
	void update();
	void animateCoins();
	void updateCoinNumberText(Essentials& essentials, const PlayerData& playerData);
	
	void drawAdequateText(Essentials& essentials, unsigned selection) const;
	void drawBagIcons(Essentials& essentials) const;
	void drawEverything(Essentials& essentials, unsigned selection);
};

}

#endif //ONE_PLAYER_SHOP_INTERFACE_H