#include "interface/mainLayout/mainFrame.h"
#include "logging/logFile.h"
#include "consts/constexprScreen.h"
#include "consts/buttonEventsID.h"
#include "consts/onePlayerGridConsts.h"
#include "wx/colour.h"
#include "wx/filedlg.h"
#include <fstream>

MainFrame::MainFrame(LogFile& logFile):
	wxFrame{ nullptr, -1, wxString{"wxEditor"}, wxPoint{-1, -1}, wxSize{ EditorWindowWidth, EditorWindowHeight} },
	logWindow{ new wxTextCtrl{ this, wxID_ANY, wxString{"Log window\n"}, wxPoint{-1, -1}, wxSize{ LogWindowWidth, LogWindowHeight }, wxTE_READONLY | wxTE_MULTILINE} },
	menusBar{},
	toolBarIcons{ this },
	notebook{ new wxNotebook{ this, -1, wxPoint{-1, -1}, wxSize{ -1, -1}, wxNB_TOP } },
	onePTextures{ logWindow },
	brickChoicePanel{ new SelectedBrickPanel{ this, onePTextures } },
	onePGrid{ new OnePlayerGridPanel{ notebook, EditorGridSquaresWidth, EditorGridSquaresHeight, onePTextures, brickChoicePanel->getBrick() } },
	
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
	SetToolBar( toolBarIcons.toolbar );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ onePGrid->resetGrid(); loadGridFromFile(event); onePGrid->Refresh(); }, fileHandling::OpenFile );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ saveCurrentOnePlayerGrid(event); }, fileHandling::SaveFile );
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
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::GenericBrick, bricks::GenericBrick::Blue); }, menuItemIds::GenericBlue );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::GenericBrick, bricks::GenericBrick::Green); }, menuItemIds::GenericGreen );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::GenericBrick, bricks::GenericBrick::Red); }, menuItemIds::GenericRed );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::GenericBrick, bricks::GenericBrick::Gray); }, menuItemIds::GenericGray );
	
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::RichBrick, bricks::RichBrick::SteelLeft); }, menuItemIds::RichSteel );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::RichBrick, bricks::RichBrick::BronzeLeft); }, menuItemIds::RichBronze );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::RichBrick, bricks::RichBrick::SilverLeft); }, menuItemIds::RichSilver );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::RichBrick, bricks::RichBrick::GoldLeft); }, menuItemIds::RichGold );
	
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::BonusCoin, 0); }, menuItemIds::BonusCoin );
	
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::GiftBrick, bricks::bonuses::BigBall); }, menuItemIds::GiftBigBall );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::GiftBrick, bricks::bonuses::SpeedUp); }, menuItemIds::GiftSpeedUp );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::GiftBrick, bricks::bonuses::SpeedDown); }, menuItemIds::GiftSpeedDown );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::GiftBrick, bricks::bonuses::ENLARGE_RIMS); }, menuItemIds::GiftEnlargeRims );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::GiftBrick, bricks::bonuses::SHRINK_RIMS); }, menuItemIds::GiftShrinkRims );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::GiftBrick, bricks::bonuses::ENLARGE_RACKET); }, menuItemIds::GiftEnlargeRacket);
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::GiftBrick, bricks::bonuses::SHRINK_RACKET); }, menuItemIds::GiftShrinkRacket );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::GiftBrick, bricks::bonuses::ONE_UP); }, menuItemIds::GiftOneUp );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::GiftBrick, bricks::bonuses::GLUE); }, menuItemIds::GiftGlueOnRacket );
	
	bindTenPointsBricks();
	
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::SolidBrick, 0); }, menuItemIds::Solid1 );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::SolidBrick, 1); }, menuItemIds::Solid2 );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::SolidBrick, 2); }, menuItemIds::Solid3 );
	
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::IceBrick, bricks::iceBricks::IceCube); }, menuItemIds::IceCubeBrick );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::IceBrick, bricks::iceBricks::PinguinBrickTexturePath); }, menuItemIds::PinguinBrickTexturePath );
	
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::HellBricks, bricks::hellBricks::SkullBrick); }, menuItemIds::SkullBrick );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::HellBricks, bricks::hellBricks::LavaStone1); }, menuItemIds::LavaStoneBrick1 );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::HellBricks, bricks::hellBricks::LavaStone2); }, menuItemIds::LavaStoneBrick2 );
	Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::HellBricks, bricks::hellBricks::LavaStone3); }, menuItemIds::LavaStoneBrick3 );
	Bind(wxEVT_COMMAND_TOOL_CLICKED, [this](wxCommandEvent& event){ if( onePGrid ){ onePGrid->shiftUpData(); onePGrid->Refresh(); } }, toolbarIcons::ShiftUpId );
	Bind(wxEVT_COMMAND_TOOL_CLICKED, [this](wxCommandEvent& event){ if( onePGrid ){ onePGrid->shiftDownData(); onePGrid->Refresh(); } }, toolbarIcons::ShiftDownId );
	
	Bind(wxEVT_COMMAND_TOOL_CLICKED, [this](wxCommandEvent& event){ if( brickChoicePanel ){ brickChoicePanel->previousCategory(); } }, toolbarIcons::CatPrevious );
	Bind(wxEVT_COMMAND_TOOL_CLICKED, [this](wxCommandEvent& event){ if( brickChoicePanel ){ brickChoicePanel->nextCategory(); } }, toolbarIcons::CatNext );
	Bind(wxEVT_COMMAND_TOOL_CLICKED, [this](wxCommandEvent& event){ if( brickChoicePanel ){ brickChoicePanel->previousSubCategory(); } }, toolbarIcons::SubCatPrevious );
	Bind(wxEVT_COMMAND_TOOL_CLICKED, [this](wxCommandEvent& event){ if( brickChoicePanel ){ brickChoicePanel->nextSubCategory(); } }, toolbarIcons::SubCatNext );
}

void MainFrame::bindTenPointsBricks()
{
	for( std::size_t i{0} ; i < TenPointsBrickStateNumber ; ++i )
	{
		Bind(wxEVT_COMMAND_MENU_SELECTED, [this, i](wxCommandEvent& event){ brickChoicePanel->setSelectedBrick(bricks::index::TenPointsBrick, i);}, menuItemIds::TenPtsVirgin + i );
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