#include "interface/mainLayout/mainFrame.h"
#include "logging/logFile.h"
#include "consts/constexprScreen.h"
#include "consts/buttonEventsID.h"
#include "consts/onePlayerGridConsts.h"
#include "wx/colour.h"
#include "wx/filedlg.h"
#include <fstream>

MainFrame::MainFrame(LogFile& logFile):
	wxFrame{ nullptr, -1, wxString{"wxEditor"}, wxPoint{-1, -1}, wxSize{ EDITOR_WINDOW_WIDTH, EDITOR_WINDOW_HEIGHT} },
	logWindow{ new wxTextCtrl{ this, wxID_ANY, wxString{"Log window\n"}, wxPoint{-1, -1}, wxSize{ LogWindowWidth, LogWindowHeight }, wxTE_READONLY | wxTE_MULTILINE} },
	menusBar{},
	notebook{ new wxNotebook{ this, -1, wxPoint{-1, -1}, wxSize{ -1, -1}, wxNB_TOP } },
	onePTextures{ logWindow },
	brickChoicePanel{ new SelectedBrickPanel{ this, onePTextures } },
	onePGrid{ new OnePlayerGridPanel{ notebook, EDITOR_GRID_SQUARES_WIDTH, EDITOR_GRID_SQUARES_HEIGHT, onePTextures, brickChoicePanel->getBrick() } },
	
	hboxSizer{ new wxBoxSizer{ wxHORIZONTAL } },
	vboxSizer{ new wxBoxSizer{ wxVERTICAL } },
	lastVBoxSizer{ new wxBoxSizer{ wxVERTICAL } }
{
	wxColour lightGrayCol{ wxT("#ededed") };
	wxColour lightBlueCol{ wxT("#ededff") };
	brickChoicePanel->SetBackgroundColour(lightGrayCol);
	notebook->AddPage(onePGrid, wxString{"brick grid"} );
	vboxSizer->Add( brickChoicePanel, 0, wxEXPAND, 10 );
	hboxSizer->Add( notebook, 0, wxALIGN_LEFT | wxALIGN_TOP, 10 );
	hboxSizer->Add( vboxSizer, 0, wxRIGHT, 10);
	lastVBoxSizer->Add(hboxSizer, 0, wxRIGHT, 0);
	lastVBoxSizer->Add( logWindow, 0, wxEXPAND );
	SetSizer(lastVBoxSizer);
	
	SetMenuBar( menusBar.menusBar );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ onePGrid->resetGrid(); loadGridFromFile(event); onePGrid->Refresh(); }, OPEN_FILE );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ saveCurrentOnePlayerGrid(event); }, SAVE_FILE );
	bindBrickChoiceMenus();
	
	logOnePBricksTextures();
}

void MainFrame::loadGridFromFile(wxCommandEvent& event)
{
		try{
			wxFileDialog openFileDialog{this, wxString{"Open a grid file"}, "", "", "*.grid", wxFD_OPEN|wxFD_FILE_MUST_EXIST};
	
			if( openFileDialog.ShowModal() == wxID_OK )
			{
				if( onePGrid )
				{
					onePGrid->loadGridFromFile(openFileDialog.GetPath().ToStdString() );
				}
				return;
			}
		}
		catch( const std::exception& e )
		{
			
		}
}

void MainFrame::saveCurrentOnePlayerGrid(wxCommandEvent& event)
{
	try{
		wxFileDialog saveFileDialog{this, wxString{"Save one player's current grid"}, 
										"", "", "*.grid", wxFD_SAVE | wxFD_OVERWRITE_PROMPT};
	
		if( saveFileDialog.ShowModal() == wxID_OK )
		{
			if( onePGrid )
			{
				onePGrid->saveGridToFile(*logWindow, saveFileDialog.GetPath().ToStdString() );
				*logWindow << "Saved '" << saveFileDialog.GetPath() << "' grid file with success.\n"; 
			}
			return;
		}
	}
	catch( const std::exception& e )
	{
		*logWindow << "Error: couldn't save grid file because: " << e.what() << " \n";
	}
}

void MainFrame::bindBrickChoiceMenus()
{
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::GEN_BRICK, BRICKS::GENERIC::BLUE); }, menuItemIds::GEN_BLUE );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::GEN_BRICK, BRICKS::GENERIC::GREEN); }, menuItemIds::GEN_GREEN );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::GEN_BRICK, BRICKS::GENERIC::RED); }, menuItemIds::GEN_RED );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::GEN_BRICK, BRICKS::GENERIC::GRAY); }, menuItemIds::GEN_GRAY );
	
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::RICH_BRICK, BRICKS::RICH::STEEL_LEFT); }, menuItemIds::RICH_STEEL );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::RICH_BRICK, BRICKS::RICH::BRONZE_LEFT); }, menuItemIds::RICH_BRONZE );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::RICH_BRICK, BRICKS::RICH::SILVER_LEFT); }, menuItemIds::RICH_SILVER );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::RICH_BRICK, BRICKS::RICH::GOLD_LEFT); }, menuItemIds::RICH_GOLD );
	
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::BONUS_COIN, 0); }, menuItemIds::BONUS_COIN );
	
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::GIFT_BRICK, BRICKS::BONUSES::BIG_BALL); }, menuItemIds::GIFT_BIG_BALL );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::GIFT_BRICK, BRICKS::BONUSES::SPEED_UP); }, menuItemIds::GIFT_SPEED_UP );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::GIFT_BRICK, BRICKS::BONUSES::SPEED_DOWN); }, menuItemIds::GIFT_SPEED_DOWN );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::GIFT_BRICK, BRICKS::BONUSES::ENLARGE_RIMS); }, menuItemIds::GIFT_ENLARGE_RIMS );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::GIFT_BRICK, BRICKS::BONUSES::SHRINK_RIMS); }, menuItemIds::GIFT_SHRINK_RIMS );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::GIFT_BRICK, BRICKS::BONUSES::ENLARGE_RACKET); }, menuItemIds::GIFT_ENLARGE_RACKET);
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::GIFT_BRICK, BRICKS::BONUSES::SHRINK_RACKET); }, menuItemIds::GIFT_SHRINK_RACKET );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::GIFT_BRICK, BRICKS::BONUSES::ONE_UP); }, menuItemIds::GIFT_ONE_UP );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::GIFT_BRICK, BRICKS::BONUSES::GLUE); }, menuItemIds::GIFT_GLUE );
	
	bindTenPointsBricks();
	
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::SOLID, 0); }, menuItemIds::SOLID_1 );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::SOLID, 1); }, menuItemIds::SOLID_2 );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::SOLID, 2); }, menuItemIds::SOLID_3 );
	
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::ICE_BRICKS, BRICKS::ICE_BR::ICE_CUBE); }, menuItemIds::ICE_CUBE_BRICK );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::ICE_BRICKS, BRICKS::ICE_BR::PINGUIN_BRICK); }, menuItemIds::PINGUIN_BRICK );
	
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::HELL_BRICKS, BRICKS::HELL_BR::SKULL_BRICK); }, menuItemIds::SKULL_BRICK );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::HELL_BRICKS, BRICKS::HELL_BR::LAVA_STONE_1); }, menuItemIds::LAVA_STONE_BRICK_1 );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::HELL_BRICKS, BRICKS::HELL_BR::LAVA_STONE_2); }, menuItemIds::LAVA_STONE_BRICK_2 );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::HELL_BRICKS, BRICKS::HELL_BR::LAVA_STONE_3); }, menuItemIds::LAVA_STONE_BRICK_3 );
}

void MainFrame::bindTenPointsBricks()
{
	for( std::size_t i{0} ; i < TENPTS_BRICK_NUM ; ++i )
	{
		Bind(wxEVT_COMMAND_MENU_SELECTED, [this, i](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(BRICKS::INDEX::TEN_POINTS, i);}, menuItemIds::TEN_PTS_VIRGIN + i );
	}
}

void MainFrame::logOnePBricksTextures()
{
	if( logWindow )
	{
		if( onePTextures.wasLoadingPerfect() )
		{
			*logWindow << "One player bricks textures were loaded perfectly.\n";
		}
		else{
			*logWindow << "There was an error while loading 'one player' bricks textures.\n";
		}
	}
}