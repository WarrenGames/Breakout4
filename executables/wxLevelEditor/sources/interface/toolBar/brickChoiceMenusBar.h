#ifndef INTERFACE_BRICK_CHOICE_MENUS_BAR_H
#define INTERFACE_BRICK_CHOICE_MENUS_BAR_H

#include "wx/menu.h"
#include <vector>

struct OneP_BrickChoiceMenusBar
{
	wxMenu *brickChoice;
	std::vector< wxMenu* > bricksCat; 			//size = bricks::index::Max
	std::vector< wxMenuItem* > genericBricks; 	//size = bricks::GenericBrick::Max
	std::vector< wxMenuItem* > richBricks;		//size = bricks::RichBrick::Max
	wxMenuItem* bonusCoinBrick;					//size = bricks::BonusCoin
	std::vector< wxMenuItem* > giftBricks;		//size = bricks::bonuses::Max
	std::vector< wxMenuItem* > tenPtsBricks;	//size = TenPointsBrickStateNumber - 1;
	std::vector< wxMenuItem* > hardBricks;
	std::vector< wxMenuItem* > iceBricks;
	std::vector< wxMenuItem* > hellBricks;
	
	OneP_BrickChoiceMenusBar();
	~OneP_BrickChoiceMenusBar() = default;
	OneP_BrickChoiceMenusBar( const OneP_BrickChoiceMenusBar& ) = delete;
	OneP_BrickChoiceMenusBar& operator= ( const OneP_BrickChoiceMenusBar& ) = delete;
	OneP_BrickChoiceMenusBar( OneP_BrickChoiceMenusBar&& ) = default;
	OneP_BrickChoiceMenusBar& operator= ( OneP_BrickChoiceMenusBar&& ) = default;
	
	void createBricksCatMenu();
	void createGenericBrickItems();
	void createRichBricks();
	void createGiftBricks();
	void createTenPtsBricks();
	void createHardBricks();
	void createIceBricks();
	void createHellBricks();
	
	void appendGenericBrickToGenCat();
	void appendRichBricksToUpperCat();
	void appendGiftBricksToBrickCat();
	void appendTenPointsBricksToBrickCat();
	void appendHardBricksToBrickCat();
	void appendIceBricksToBrickCat();
	void appendHellBricksToBrickCat();
	
	void appendBrickCatToBrickChoice();
	
	void enableAllMenuItems(bool isEnabled);
	void enableGenericBrickItems(bool isEnabled);
	void enableRichBricksItems(bool isEnabled);
	void enableGiftBricksItem(bool isEnabled);
	void enableTenPointsBricksItem(bool isEnabled);
	void enableHardBricksItem(bool isEnabled);
	void enableIceBricksItem(bool isEnabled);
	void enableHellBricksItem(bool isEnabled);
};

#endif //INTERFACE_BRICK_CHOICE_MENUS_BAR_H