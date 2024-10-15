#include "interface/menuBar.h"
#include "interface/menuItemsID.h"

MenuBar::MenuBar():
	menuBar{ new wxMenuBar },
	file{ new wxMenu },
	setValues{ new wxMenu },
	checking{ new wxMenu },
	setSkillLevel{ new wxMenu },
	setRacketSize{ new wxMenu },
	setRimState{ new wxMenu },
	setCampaignType{ new wxMenu },
	setHeadersStrings{ new wxMenu },
	loadGameSave{ new wxMenuItem{ file, menuItemsID::LoadWithDialogWindow, wxString{"Load game save"} } },
	saveGameSave{ new wxMenuItem{ file, menuItemsID::SaveWithDialogWindow, wxString{"Save game save"} } },
	checkCurrentSave{ new wxMenuItem{ checking, menuItemsID::CheckingRef, wxString{"Check current save"} } },
	setSlotInfos{ new wxMenuItem{ checking, menuItemsID::SetSlotInfo, wxString{"Set slot infos before saving"} } },
	easySkill{ new wxMenuItem{ setSkillLevel, menuItemsID::SetSkillToEasy, wxString{"Set skill to easy"} } },
	mediumSkill{ new wxMenuItem{ setSkillLevel, menuItemsID::SetSkillToMedium, wxString{"Set skill to medium"} } },
	hardSkill{ new wxMenuItem{ setSkillLevel, menuItemsID::SetSkillToHard, wxString{"Set skill to hard"} } },
	smallRacket{ new wxMenuItem{ setRacketSize, menuItemsID::SmallRacket, wxString{"Small racket"} } },
	mediumRacket{ new wxMenuItem{ setRacketSize, menuItemsID::MediumRacket, wxString{"Medium racket"} } },
	largeRacket{ new wxMenuItem{ setRacketSize, menuItemsID::LargeRacket, wxString{"LargeRacket"} } },
	campaignWithShop{ new wxMenuItem{ setCampaignType, menuItemsID::CampaignWithShop, wxString{"Campaign with shop"} } },
	campaignNoShop{ new wxMenuItem{ setCampaignType, menuItemsID::CampaignNoShop, wxString{"Campaign without shop"} } },
	setCampaignHeader{ new wxMenuItem{ setHeadersStrings, menuItemsID::CampaignHeaderString, wxString{"Campaign header"} } },
	setScoreHeader{ new wxMenuItem{ setHeadersStrings, menuItemsID::ScoreHeaderString, wxString{"Score header"} } }
{
	createRimEvenNumber();
	file->Append(loadGameSave);
	file->Append(saveGameSave);
	setSkillLevel->Append(easySkill);
	setSkillLevel->Append(mediumSkill);
	setSkillLevel->Append(hardSkill);
	setRacketSize->Append(smallRacket);
	setRacketSize->Append(mediumRacket);
	setRacketSize->Append(largeRacket);
	appendRimMenuItems();
	setCampaignType->Append(campaignWithShop);
	setCampaignType->Append(campaignNoShop);
	setHeadersStrings->Append(setCampaignHeader);
	setHeadersStrings->Append(setScoreHeader);
	setValues->AppendSubMenu(setSkillLevel, wxString{"Set skill level"} );
	setValues->AppendSubMenu(setRacketSize, wxString{"Set racket size"} );
	setValues->AppendSubMenu(setRimState, wxString{"Set rim even"} );
	setValues->AppendSubMenu(setCampaignType, wxString{"Set campaign type"} );
	setValues->AppendSubMenu(setHeadersStrings, wxString{"Set headers strings"} );
	checking->Append(checkCurrentSave);
	checking->Append(setSlotInfos);
	menuBar->Append(file, wxString{"Saves"} );
	menuBar->Append(setValues, wxString{"Set values"} );
	menuBar->Append(checking, wxString{"Checking"} );
}

void MenuBar::createRimEvenNumber()
{
	rimState.emplace_back( new wxMenuItem{setRimState, menuItemsID::RimNull, wxString{"No rim at all"} } );
	rimState.emplace_back( new wxMenuItem{setRimState, menuItemsID::Rim1, wxString{"1 rim even"} } );
	rimState.emplace_back( new wxMenuItem{setRimState, menuItemsID::Rim2, wxString{"2 rim even"} } );
	rimState.emplace_back( new wxMenuItem{setRimState, menuItemsID::Rim3, wxString{"3 rim even"} } );
}

void MenuBar::appendRimMenuItems()
{
	for( auto &rim : rimState )
	{
		setRimState->Append( rim );
	}
}