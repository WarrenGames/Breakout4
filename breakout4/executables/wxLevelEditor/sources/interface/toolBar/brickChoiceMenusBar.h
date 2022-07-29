#ifndef INTERFACE_BRICK_CHOICE_MENUS_BAR_H
#define INTERFACE_BRICK_CHOICE_MENUS_BAR_H

#include "wx/menu.h"
#include <vector>

struct OneP_BrickChoiceMenusBar
{
	wxMenu *brickChoice;
	std::vector< wxMenu* > bricksCat; 			//size = BRICKS::INDEX::MAX
	std::vector< wxMenuItem* > genericBricks; 	//size = BRICKS::GENERIC::MAX
	std::vector< wxMenuItem* > richBricks;		//size = BRICKS::RICH::MAX
	wxMenuItem* bonusCoinBrick;					//size = BRICKS::BONUS_COIN
	std::vector< wxMenuItem* > giftBricks;		//size = BRICKS::BONUSES::MAX
	std::vector< wxMenuItem* > tenPtsBricks;	//size = TENPTS_BRICK_NUM - 1;
	std::vector< wxMenuItem* > hardBricks;
	std::vector< wxMenuItem* > iceBricks;
	std::vector< wxMenuItem* > hellBricks;
	
	OneP_BrickChoiceMenusBar();
	
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