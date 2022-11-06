#include "interface/myFrame.h"
#include "appStart/appStartData.h"
#include "prefPath/wxPrefPath.h"
#include "data/gameSavePath.h"
#include "data/fileSaving.h"
#include "data/fileLoading.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "time/dateAndTime.h"
#include "consts/consts.h"
#include "interface/menuItemsID.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/rimsConsts.h"
#include "gameSlots/slotConsts.h"
#include "wx/filedlg.h"
#include "wx/string.h"
#include <stdexcept>

MyFrame::MyFrame(AppStartData& appStartData):
	wxFrame{ nullptr, wxID_ANY, FrameTitle, wxDefaultPosition, wxSize{ WindowWidth, WindowHeight } },
	notebook{ new wxNotebook{ this, wxID_ANY, wxPoint{ -1, -1}, wxSize{ WindowWidth, WindowHeight }, 0, "notebook" } },
	logWindow{ new wxTextCtrl{ this, wxID_ANY, wxString{"Log window\n"}, wxPoint{-1, -1}, wxSize{LogWindowWidth, LogWindowHeight}, wxTE_READONLY | wxTE_MULTILINE} },
	vBoxSizer{ new wxBoxSizer{ wxVERTICAL } },
	headerInterface{ notebook, appStartData.headersTexts },
	gameObjectsInterface{ notebook, appStartData.gameObjectsTexts },
	bagBonusesInterface{ notebook, appStartData.bagBonusesTexts },
	prefPath{appStartData.prefPath},
	logs{appStartData.logs},
	headersTexts{logs.error, getCampaignLocaleTextsFile("english", file::ONE_PLAY_SAVE_AND_LOAD), SaveNameFocusingGameMax},
	gameSavePath{ getGameSavesPath(prefPath) }
{
	vBoxSizer->Add(notebook, 1, wxEXPAND );
	vBoxSizer->Add(logWindow, 0, wxEXPAND );
	
	SetSizer(vBoxSizer);
	SetMenuBar( menuBar.menuBar );
	
	bindMenuBar();
	logPrefPathStatus();
	atStartLogging(appStartData);
	
	setWidgetsWithLoadedSlot();
}

void MyFrame::bindMenuBar()
{
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ loadFromFileDialog(event);	},	menuItemsID::LoadWithDialogWindow ); 
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ saveToFileDialog(event); }, menuItemsID::SaveWithDialogWindow ); 
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ checkTextCtrlValues(); }, menuItemsID::CheckingRef );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ setCurrentValuesToSlot(); }, menuItemsID::SetSlotInfo );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ bindSkillLevelMenu(event); }, menuItemsID::SetSkillToEasy, menuItemsID::SetSkillToHard );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ bindCampaignType(event); }, menuItemsID::CampaignWithShop, menuItemsID::CampaignNoShop );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ bindRacketSize(event); }, menuItemsID::SmallRacket, menuItemsID::LargeRacket );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ bindRimSize(event); }, menuItemsID::RimNull, menuItemsID::Rim3 );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ bindCampaignHeaderMenu(event); }, menuItemsID::CampaignHeaderString );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ bindScoreHeaderMenu(event); }, menuItemsID::ScoreHeaderString );
}

void MyFrame::bindSkillLevelMenu(wxCommandEvent& event)
{
	const int id{ event.GetId() };
	assert( id >= menuItemsID::SetSkillToEasy && id <= menuItemsID::SetSkillToHard );
	gameObjectsInterface.setValue(IndexSkillLevel, id - menuItemsID::SetSkillToEasy, onePlGame::SkillLevelMax);
}

void MyFrame::bindCampaignType(wxCommandEvent& event)
{
	const int id{ event.GetId() };
	assert( id == menuItemsID::CampaignWithShop || id == menuItemsID::CampaignNoShop );
	gameObjectsInterface.setValue(IndexCampaignType, id - menuItemsID::CampaignWithShop, onePlGame::CampaignMax);
}

void MyFrame::bindRacketSize(wxCommandEvent& event)
{
	const int id{ event.GetId() };
	assert( id >= menuItemsID::SmallRacket && id <= menuItemsID::LargeRacket );
	gameObjectsInterface.setValue(IndexRacketSize, id - menuItemsID::SmallRacket, onePlGame::RacketMax );
}

void MyFrame::bindRimSize(wxCommandEvent& event)
{
	const int id{ event.GetId() };
	assert( id >= menuItemsID::RimNull && id <= menuItemsID::Rim3 );
	gameObjectsInterface.setValue(IndexRimState, id - menuItemsID::RimNull + rims::RimNullState, rims::RimNullState, rims::RemoveMax);
}

void MyFrame::bindCampaignHeaderMenu(wxCommandEvent& event)
{
	if( savesSlots.slot.gameType < onePlGame::CampaignMax )
	{
		try{
			savesSlots.slot.setCampaign(headersTexts);
			savesSlots.slot.addDateToString();
			headerInterface.eraseTextCtrlContent(HeaderCampaignAndDate);
			headerInterface.appendTextToWidget(savesSlots.slot.campaignAndDateInfos, HeaderCampaignAndDate);
		}
		catch( const std::exception& e )
		{
			if( logWindow )
			{
				*logWindow << "Error: exception thrown while setting campaign header string: " << e.what() << " .\n";
			}
		}
	}
	else{
		if( logWindow )
		{
			*logWindow << "Error: bad 'Campaign type' value. Should be equal to '" << onePlGame::CampaignWithShop << "' or '" << onePlGame::CampaignNoShop << "' .\n";
		}
	}
}

void MyFrame::bindScoreHeaderMenu(wxCommandEvent& event)
{
	try{
		savesSlots.slot.setScoreAndCoins(headersTexts);
		headerInterface.eraseTextCtrlContent(HeaderScoreAndCoin);
		if( savesSlots.slot.scoreAndCoinsInfos.empty() )
		{
			throw std::runtime_error{"Error: the 'scoreAndCoinsInfos' std::string is empty."};
		}
		else{
			headerInterface.appendTextToWidget(savesSlots.slot.scoreAndCoinsInfos, HeaderScoreAndCoin);
		}
	}
	catch( const std::exception& e )
	{
		if( logWindow )
		{
			*logWindow << "Error: exception thrown while setting scoreAndCoin header string: " << e.what() << " .\n";
		}
	}
}

void MyFrame::setWidgetsWithLoadedSlot()
{
	try{
		headerInterface.setTextCtrl(savesSlots.slot);
		gameObjectsInterface.setTextCtrlData(savesSlots.slot);
		bagBonusesInterface.setTextCtrl(savesSlots.slot);
	}
	catch( const std::exception& e )
	{
		*logWindow << "Error: fail to set value of wxTextCtrl with loaded data from game save: " << e.what() << " \n";
	}
}

//Checks if slot is valid
void MyFrame::checkTextCtrlValues() const
{
	if( logWindow )
	{
		GameSlotData dummySlot;
		try{
			runAssignations(dummySlot);
			*logWindow << "Checking current data in wxTextCtrl done with success !\n";
		}
		catch( const std::exception& e )
		{
			*logWindow << "Error: exception thrown while checking wxTextCtrl value with 'SaveSlotInfos' data: " << e.what() << " .\n";
		}
	}
}

void MyFrame::runAssignations(GameSlotData& slot) const
{
	headerInterface.checkTextCtrl(HeaderCampaignAndDate, "Header campaign and date", slot.campaignAndDateInfos);
	headerInterface.checkTextCtrl(HeaderScoreAndCoin, "Header score and coin", slot.scoreAndCoinsInfos);
	gameObjectsInterface.checkTextCtrl(slot);
	bagBonusesInterface.checkTextCtrl(slot);
}

void MyFrame::saveToFileDialog(wxCommandEvent& event)
{
	if( logWindow )
	{
		if( prefPath )
		{
			try{
				wxFileDialog saveFileDialog{this, "Save slot data", gameSavePath, "", "*.save", wxFD_SAVE | wxFD_OVERWRITE_PROMPT};
				if( saveFileDialog.ShowModal() == wxID_OK )
				{
					saveGameSlot(*logWindow, savesSlots.slot, saveFileDialog.GetPath().ToStdString() );
					return;
				}
			}
			catch( const std::exception& e )
			{
				*logWindow << "Exception thrown: " << e.what() << "\n";
			}
		}
		else{
			*logWindow << "No pref path found, can't open dialog file, reason: " << prefPath.getError() << ".\n";
		}
	}
}

void MyFrame::loadFromFileDialog(wxCommandEvent& event)
{
	if( logWindow )
	{
		if( prefPath )
		{
			try{
				wxFileDialog openFileDialog{this, "Open a game save file", gameSavePath, "", "*.save", wxFD_OPEN|wxFD_FILE_MUST_EXIST};

				if( openFileDialog.ShowModal() == wxID_OK )
				{
					loadGameSlot(*logWindow, savesSlots.slot, openFileDialog.GetPath().ToStdString() );
					setWidgetsWithLoadedSlot();
					return;
				}
			}
			catch( const std::exception& e )
			{
				*logWindow << "Exception thrown: " << e.what() << "\n";
			}
		}
		else{
			*logWindow << "No pref path found, can't open dialog file, reason: " << prefPath.getError() << ".\n";
		}
	}
}

void MyFrame::setCurrentValuesToSlot()
{
	if( logWindow )
	{
		try{
			runAssignations(savesSlots.slot);
			*logWindow << "Assignations to slot data done with success !\n";
		}
		catch( const std::exception& e )
		{
			*logWindow << "Error: exception thrown while processing assignation from wxTextCtrls values with 'SaveSlotInfos' data: " << e.what() << " .\n";
		}
	}
}

void MyFrame::logPrefPathStatus()
{
	if( logWindow )
	{
		if( prefPath )
		{
			*logWindow << "Pref path was found: '" << prefPath.getPath() << "' \n";
		}
		else
		{
			*logWindow << "Pref path not found, because: " << prefPath.getError() << " \n";
		}
	}
}

void MyFrame::atStartLogging(const AppStartData& appStartData)
{
	if( logWindow )
	{
		*logWindow << "Save headers texts loading status: " << appStartData.headersTexts << " \n";
		*logWindow << "Game objects texts loading status: " << appStartData.gameObjectsTexts << " \n";
		*logWindow << "Bag bonuses texts loading status: " << appStartData.bagBonusesTexts << " \n";
		//*logWindow << "Headers locale texts loading status: " << appStartData.campaignLocaleTexts << " \n";
	}
}