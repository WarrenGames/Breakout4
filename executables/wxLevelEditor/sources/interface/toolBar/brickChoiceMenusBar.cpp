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
	bonusCoinBrick = new wxMenuItem{ bricksCat[bricks::index::BonusCoin], menuItemIds::BonusCoin, wxT("Bonus coin brick") }; 
	
	appendGenericBrickToGenCat();
	appendRichBricksToUpperCat();
	bricksCat[bricks::index::BonusCoin]->Append(bonusCoinBrick);
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
	
	for( std::size_t i{0} ; i < bricks::index::Max ; ++i )
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
	std::vector< int > menuId{ menuItemIds::GenericBlue, menuItemIds::GenericGreen, menuItemIds::GenericRed, menuItemIds::GenericGray };
	
	for( std::size_t i{0} ; i < bricks::GenericBrick::Max ; ++i )
	{
		genericBricks.emplace_back( new wxMenuItem{bricksCat[bricks::index::GenericBrick], menuId[i], texts[i]} );
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
	std::vector< int > menuId{ menuItemIds::RichSteel, menuItemIds::RichBronze, menuItemIds::RichSilver, menuItemIds::RichGold };
	
	for( std::size_t i{0} ; i < texts.size() ; ++i )
	{
		richBricks.emplace_back( new wxMenuItem{bricksCat[bricks::index::RichBrick], menuId[i], texts[i]} );
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
	
	std::vector< int > menuId{ 	menuItemIds::GiftBigBall, 
								menuItemIds::GiftSpeedUp,
								menuItemIds::GiftSpeedDown, 
								menuItemIds::GiftEnlargeRims,
								menuItemIds::GiftShrinkRims,
								menuItemIds::GiftEnlargeRacket,
								menuItemIds::GiftShrinkRacket,
								menuItemIds::GiftOneUp,
								menuItemIds::GiftGlueOnRacket
						};
	
	for( std::size_t i{0} ; i < texts.size() ; ++i )
	{
		giftBricks.emplace_back( new wxMenuItem{ bricksCat[bricks::index::GiftBrick], menuId[i], texts[i] } );
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
	for( std::size_t i{0} ; i < TenPointsBrickStateNumber ; ++i )
	{
		tenPtsId.emplace_back( static_cast<int>(i) + menuItemIds::TenPtsVirgin );
	}
	
	for( std::size_t i{0} ; i < texts.size() ; ++i )
	{
		tenPtsBricks.emplace_back( new wxMenuItem{ bricksCat[bricks::index::TenPointsBrick], tenPtsId[i], texts[i] } );
	}
}

void OneP_BrickChoiceMenusBar::createHardBricks()
{
	hardBricks.emplace_back( new wxMenuItem{ bricksCat[bricks::index::SolidBrick], menuItemIds::Solid1, "Hard brick 1"} );
	hardBricks.emplace_back( new wxMenuItem{ bricksCat[bricks::index::SolidBrick], menuItemIds::Solid2, "Hard brick 2"} );
	hardBricks.emplace_back( new wxMenuItem{ bricksCat[bricks::index::SolidBrick], menuItemIds::Solid3, "Hard brick 3"} );
}

void OneP_BrickChoiceMenusBar::createIceBricks()
{
	std::vector< wxString > texts
	{
		wxT("Ice cube brick"),
		wxT("Pinguin brick")
	};
	
	std::vector< int > menuIds{ menuItemIds::IceCubeBrick, menuItemIds::PinguinBrickTexturePath };
	
	for( std::size_t i{0} ; i < texts.size() ; ++i )
	{
		iceBricks.emplace_back( new wxMenuItem{ bricksCat[bricks::index::IceBrick], menuIds[i], texts[i] } );
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
	std::vector< int > menuIds{ menuItemIds::SkullBrick, menuItemIds::LavaStoneBrick1, menuItemIds::LavaStoneBrick2, menuItemIds::LavaStoneBrick3 };
	
	for( std::size_t i{0} ; i < texts.size() ; ++i )
	{
		hellBricks.emplace_back( new wxMenuItem{ bricksCat[bricks::index::HellBricks], menuIds[i], texts[i] } );
	}
}

void OneP_BrickChoiceMenusBar::appendGenericBrickToGenCat()
{
	for( auto &menu : genericBricks )
	{
		bricksCat[bricks::index::GenericBrick]->Append(menu);
	}
}

void OneP_BrickChoiceMenusBar::appendRichBricksToUpperCat()
{
	for( auto &menu : richBricks )
	{
		bricksCat[bricks::index::RichBrick]->Append(menu);
	}
}

void OneP_BrickChoiceMenusBar::appendGiftBricksToBrickCat()
{
	for( auto &menu : giftBricks )
	{
		bricksCat[bricks::index::GiftBrick]->Append(menu);
	}
}

void OneP_BrickChoiceMenusBar::appendTenPointsBricksToBrickCat()
{
	for( auto &menu : tenPtsBricks )
	{
		bricksCat[bricks::index::TenPointsBrick]->Append(menu);
	}
}

void OneP_BrickChoiceMenusBar::appendHardBricksToBrickCat()
{
	for( auto &menu : hardBricks )
	{
		bricksCat[bricks::index::SolidBrick]->Append(menu);
	}
}

void OneP_BrickChoiceMenusBar::appendIceBricksToBrickCat()
{
	for( auto &menu : iceBricks )
	{
		bricksCat[bricks::index::IceBrick]->Append(menu);
	}
}

void OneP_BrickChoiceMenusBar::appendHellBricksToBrickCat()
{
	for( auto &menu : hellBricks )
	{
		bricksCat[bricks::index::HellBricks]->Append(menu);
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