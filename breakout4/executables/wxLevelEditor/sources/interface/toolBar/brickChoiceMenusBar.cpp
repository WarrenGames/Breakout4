#include "interface/toolBar/brickChoiceMenusBar.h"
#include "consts/onePlayerGridConsts.h"
#include "consts/buttonEventsID.h"
#include <cassert>

OneP_BrickChoiceMenusBar::OneP_BrickChoiceMenusBar():
	brickChoice{ new wxMenu{ } }
{
	createBricksCatMenu();
	createGenericBrickItems();
	createRichBricks();
	createGiftBricks();
	createHardBricks();
	createTenPtsBricks();
	createIceBricks();
	createHellBricks();
	bonusCoinBrick = new wxMenuItem{ bricksCat[BRICKS::INDEX::BONUS_COIN], menuItemIds::BONUS_COIN, wxT("Bonus coin brick") }; 
	
	appendGenericBrickToGenCat();
	appendRichBricksToUpperCat();
	bricksCat[BRICKS::INDEX::BONUS_COIN]->Append(bonusCoinBrick);
	appendGiftBricksToBrickCat();
	appendTenPointsBricksToBrickCat();
	appendHardBricksToBrickCat();
	appendIceBricksToBrickCat();
	appendHellBricksToBrickCat();
	
	appendBrickCatToBrickChoice();
	
	enableAllMenuItems(true);
}

void OneP_BrickChoiceMenusBar::createBricksCatMenu()
{
	std::vector< wxString > texts
	{
		wxT("No brick"),
		wxT("Generic bricks"),
		wxT("Rich brick"),
		wxT("Bonus coin"),
		wxT("Gift brick"),
		wxT("Ten points"),
		wxT("Solid"),
		wxT("Ice bricks"),
		wxT("Hell bricks")
	};
	
	for( std::size_t i{0} ; i < BRICKS::INDEX::MAX ; ++i )
	{
		bricksCat.emplace_back( new wxMenu{texts[i]} );
	}
}

void OneP_BrickChoiceMenusBar::createGenericBrickItems()
{
	std::vector< wxString > texts
	{
		wxT("Blue brick"),
		wxT("Green brick"),
		wxT("Red brick"),
		wxT("Gray brick")
	};
	std::vector< int > menuId{ menuItemIds::GEN_BLUE, menuItemIds::GEN_GREEN, menuItemIds::GEN_RED, menuItemIds::GEN_GRAY };
	
	for( std::size_t i{0} ; i < BRICKS::GENERIC::MAX ; ++i )
	{
		genericBricks.emplace_back( new wxMenuItem{bricksCat[BRICKS::INDEX::GEN_BRICK], menuId[i], texts[i]} );
	}
}

void OneP_BrickChoiceMenusBar::createRichBricks()
{
	std::vector< wxString > texts
	{
		wxT("Steel brick"),
		wxT("Bronze brick"),
		wxT("Silver brick"),
		wxT("Gold brick")
	};
	std::vector< int > menuId{ menuItemIds::RICH_STEEL, menuItemIds::RICH_BRONZE, menuItemIds::RICH_SILVER, menuItemIds::RICH_GOLD };
	
	for( std::size_t i{0} ; i < texts.size() ; ++i )
	{
		richBricks.emplace_back( new wxMenuItem{bricksCat[BRICKS::INDEX::RICH_BRICK], menuId[i], texts[i]} );
	}
}

void OneP_BrickChoiceMenusBar::createGiftBricks()
{
	std::vector< wxString > texts
	{
		wxT("Big ball"),
		wxT("Speed up"),
		wxT("Speed down"),
		wxT("Enlarge rims"),
		wxT("Shrink rims"),
		wxT("Enlarge racket"),
		wxT("Shrink racket"),
		wxT("One up"),
		wxT("Glue racket")
	};
	
	std::vector< int > menuId{ 	menuItemIds::GIFT_BIG_BALL, 
								menuItemIds::GIFT_SPEED_UP,
								menuItemIds::GIFT_SPEED_DOWN, 
								menuItemIds::GIFT_ENLARGE_RIMS,
								menuItemIds::GIFT_SHRINK_RIMS,
								menuItemIds::GIFT_ENLARGE_RACKET,
								menuItemIds::GIFT_SHRINK_RACKET,
								menuItemIds::GIFT_ONE_UP,
								menuItemIds::GIFT_GLUE
						};
	
	for( std::size_t i{0} ; i < texts.size() ; ++i )
	{
		giftBricks.emplace_back( new wxMenuItem{ bricksCat[BRICKS::INDEX::GIFT_BRICK], menuId[i], texts[i] } );
	}
}

void OneP_BrickChoiceMenusBar::createTenPtsBricks()
{
	std::vector< wxString > texts
	{
		wxT("Virgin brick"),
		wxT("Once hit brick"),
		wxT("Twice hit brick"),
		wxT("Three times hit brick"),
		wxT("Four times hit brick"),
		wxT("Five times hit brick"),
		wxT("Six times hit brick"),
		wxT("Seven times hit brick")
	};
	
	std::vector< int > tenPtsId;
	for( std::size_t i{0} ; i < TENPTS_BRICK_NUM ; ++i )
	{
		tenPtsId.emplace_back( static_cast<int>(i) + menuItemIds::TEN_PTS_VIRGIN );
	}
	
	for( std::size_t i{0} ; i < texts.size() ; ++i )
	{
		tenPtsBricks.emplace_back( new wxMenuItem{ bricksCat[BRICKS::INDEX::TEN_POINTS], tenPtsId[i], texts[i] } );
	}
}

void OneP_BrickChoiceMenusBar::createHardBricks()
{
	hardBricks.emplace_back( new wxMenuItem{ bricksCat[BRICKS::INDEX::SOLID], menuItemIds::SOLID_1, "Hard brick 1"} );
	hardBricks.emplace_back( new wxMenuItem{ bricksCat[BRICKS::INDEX::SOLID], menuItemIds::SOLID_2, "Hard brick 2"} );
	hardBricks.emplace_back( new wxMenuItem{ bricksCat[BRICKS::INDEX::SOLID], menuItemIds::SOLID_3, "Hard brick 3"} );
}

void OneP_BrickChoiceMenusBar::createIceBricks()
{
	std::vector< wxString > texts
	{
		wxT("Ice cube brick"),
		wxT("Pinguin brick")
	};
	
	std::vector< int > menuIds{ menuItemIds::ICE_CUBE_BRICK, menuItemIds::PINGUIN_BRICK };
	
	for( std::size_t i{0} ; i < texts.size() ; ++i )
	{
		iceBricks.emplace_back( new wxMenuItem{ bricksCat[BRICKS::INDEX::ICE_BRICKS], menuIds[i], texts[i] } );
	}
}

void OneP_BrickChoiceMenusBar::createHellBricks()
{
	std::vector< wxString > texts
	{
		wxT("Skull brick"),
		wxT("Lava stone brick 1"),
		wxT("Lava stone brick 2"),
		wxT("Lava stone brick 3")
	};
	std::vector< int > menuIds{ menuItemIds::SKULL_BRICK, menuItemIds::LAVA_STONE_BRICK_1, menuItemIds::LAVA_STONE_BRICK_2, menuItemIds::LAVA_STONE_BRICK_3 };
	
	for( std::size_t i{0} ; i < texts.size() ; ++i )
	{
		hellBricks.emplace_back( new wxMenuItem{ bricksCat[BRICKS::INDEX::HELL_BRICKS], menuIds[i], texts[i] } );
	}
}

void OneP_BrickChoiceMenusBar::appendGenericBrickToGenCat()
{
	for( auto &menu : genericBricks )
	{
		bricksCat[BRICKS::INDEX::GEN_BRICK]->Append(menu);
	}
}

void OneP_BrickChoiceMenusBar::appendRichBricksToUpperCat()
{
	for( auto &menu : richBricks )
	{
		bricksCat[BRICKS::INDEX::RICH_BRICK]->Append(menu);
	}
}

void OneP_BrickChoiceMenusBar::appendGiftBricksToBrickCat()
{
	for( auto &menu : giftBricks )
	{
		bricksCat[BRICKS::INDEX::GIFT_BRICK]->Append(menu);
	}
}

void OneP_BrickChoiceMenusBar::appendTenPointsBricksToBrickCat()
{
	for( auto &menu : tenPtsBricks )
	{
		bricksCat[BRICKS::INDEX::TEN_POINTS]->Append(menu);
	}
}

void OneP_BrickChoiceMenusBar::appendHardBricksToBrickCat()
{
	for( auto &menu : hardBricks )
	{
		bricksCat[BRICKS::INDEX::SOLID]->Append(menu);
	}
}

void OneP_BrickChoiceMenusBar::appendIceBricksToBrickCat()
{
	for( auto &menu : iceBricks )
	{
		bricksCat[BRICKS::INDEX::ICE_BRICKS]->Append(menu);
	}
}

void OneP_BrickChoiceMenusBar::appendHellBricksToBrickCat()
{
	for( auto &menu : hellBricks )
	{
		bricksCat[BRICKS::INDEX::HELL_BRICKS]->Append(menu);
	}
}

void OneP_BrickChoiceMenusBar::appendBrickCatToBrickChoice()
{
	for( auto &menu : bricksCat )
	{
		brickChoice->AppendSubMenu( menu, menu->GetTitle() );
	}
}

void OneP_BrickChoiceMenusBar::enableAllMenuItems(bool isEnabled)
{
	enableGenericBrickItems(isEnabled);
	enableRichBricksItems(isEnabled);
	enableGiftBricksItem(isEnabled);
	enableTenPointsBricksItem(isEnabled);
	enableHardBricksItem(isEnabled);
	enableIceBricksItem(isEnabled);
	enableHellBricksItem(isEnabled);
}

void OneP_BrickChoiceMenusBar::enableGenericBrickItems(bool isEnabled)
{
	for( auto &menuItem : genericBricks )
	{
		menuItem->Enable(isEnabled);
	}
}

void OneP_BrickChoiceMenusBar::enableRichBricksItems(bool isEnabled)
{
	for( auto &menuItem : richBricks )
	{
		menuItem->Enable(isEnabled);
	}
}

void OneP_BrickChoiceMenusBar::enableGiftBricksItem(bool isEnabled)
{
	for( auto &menuItem : giftBricks )
	{
		menuItem->Enable(isEnabled);
	}
}

void OneP_BrickChoiceMenusBar::enableTenPointsBricksItem(bool isEnabled)
{
	for( auto &menuItem : tenPtsBricks )
	{
		menuItem->Enable(isEnabled);
	}
}

void OneP_BrickChoiceMenusBar::enableHardBricksItem(bool isEnabled)
{
	for( auto &menuItem : hardBricks )
	{
		menuItem->Enable(isEnabled);
	}
}

void OneP_BrickChoiceMenusBar::enableIceBricksItem(bool isEnabled)
{
	for( auto &menuItem : iceBricks )
	{
		menuItem->Enable(isEnabled);
	}
}

void OneP_BrickChoiceMenusBar::enableHellBricksItem(bool isEnabled)
{
	for( auto &menuItem : hellBricks )
	{
		menuItem->Enable(isEnabled);
	}
}