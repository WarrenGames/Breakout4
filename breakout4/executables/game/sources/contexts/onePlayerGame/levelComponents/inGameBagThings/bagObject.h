#ifndef ONE_PLAYER_BAG_OBJECT_H
#define ONE_PLAYER_BAG_OBJECT_H

#include "contexts/onePlayerGame/levelComponents/inGameBagThings/bonusesCountGraphics.h"

struct PlayerBag
{
	std::vector<TextureCombo> bagIcons;
	BonusesCountGraphics bonusesCount;
	unsigned selectedBonus;
	SDL_Rect selectionRect;
	bool quitBagView;
	
	explicit PlayerBag(Essentials& essentials, const PlayerData& playerData);
	~PlayerBag() = default;
	PlayerBag( const PlayerBag& ) = delete;
	PlayerBag& operator= ( const PlayerBag& ) = delete;
	PlayerBag( PlayerBag&& ) = default;
	PlayerBag& operator= ( PlayerBag&& ) = default;
	
	int getSquareXCoord();
	
	void selectForward();
	void selectBackward();
	
	void drawBagIcons(Essentials& essentials) const;
	void drawEverything(Essentials& essentials) const;
};

#endif //ONE_PLAYER_BAG_OBJECT_H