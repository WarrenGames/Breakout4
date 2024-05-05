#ifndef ONE_PLAYER_BONUSES_SHOP_H
#define ONE_PLAYER_BONUSES_SHOP_H

struct Essentials;
struct PlayerData;
struct Offset;
struct SDL_Rect;

namespace onePlayerShop{
	struct ShopInterface;
	
	void context(Essentials& essentials, PlayerData& playerData);
	
	void drawEverything(Essentials& essentials, onePlayerShop::ShopInterface& shopInterface, unsigned selection);
	
	bool isMouseOverStickyJar(const Offset& mousePosition);
	
	bool isMouseOverSpeedUpJar(const Offset& mousePosition);
	
	bool isMouseOverEnlargeRacketJar(const Offset& mousePosition);
	
	bool isMouseOverEnlargeRimJar(const Offset& mousePosition);
	
	bool isMouseOverPowerBallJar(const Offset& mousePosition);
	
	bool isMouseOverOneUpJar(const Offset& mousePosition);
	
	bool isPointInRect(const Offset& mousePosition, const SDL_Rect& rect);
	
	void setMouseSelection(unsigned& selection, const Offset& mousePosition);
	
	void quitShop(Essentials& essentials, bool& quitShop);
	
	void actAccordinglyToEvent(Essentials& essentials, onePlayerShop::ShopInterface& shopInterface, PlayerData& playerData, unsigned& selection, bool& quitShop);
	
	void buyABonus(Essentials& essentials, onePlayerShop::ShopInterface& shopInterface, PlayerData& playerData, unsigned& selection);
}

#endif //ONE_PLAYER_BONUSES_SHOP_H