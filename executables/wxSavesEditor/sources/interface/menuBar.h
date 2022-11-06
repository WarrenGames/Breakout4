#ifndef SAVES_EDITOR_MENU_BAR_H
#define SAVES_EDITOR_MENU_BAR_H

#include <wx/menu.h>
#include <wx/menuitem.h>
#include <vector>

struct MenuBar
{
	wxMenuBar *menuBar;
	
	wxMenu *file;
	wxMenu *setValues;
	wxMenu *checking;
	
	wxMenu *setSkillLevel;
	wxMenu *setRacketSize;
	wxMenu *setRimState;
	wxMenu *setCampaignType;
	wxMenu *setHeadersStrings;
	
	wxMenuItem *loadGameSave;
	wxMenuItem *saveGameSave;
	wxMenuItem *checkCurrentSave;
	wxMenuItem *setSlotInfos;
	
	wxMenuItem *easySkill;
	wxMenuItem *mediumSkill;
	wxMenuItem *hardSkill;
	
	wxMenuItem *smallRacket;
	wxMenuItem *mediumRacket;
	wxMenuItem *largeRacket;
	
	wxMenuItem *campaignWithShop;
	wxMenuItem *campaignNoShop;
	
	wxMenuItem *setCampaignHeader;
	wxMenuItem *setScoreHeader;
	
	std::vector< wxMenuItem* > rimState;
	
	explicit MenuBar();
	~MenuBar() = default;
	MenuBar( const MenuBar& ) = delete;
	MenuBar& operator= ( const MenuBar& ) = delete;
	MenuBar( MenuBar&& ) = default;
	MenuBar& operator= ( MenuBar&& ) = default;
	
	void createRimEvenNumber();
	void appendRimMenuItems();
};

#endif //SAVES_EDITOR_MENU_BAR_H