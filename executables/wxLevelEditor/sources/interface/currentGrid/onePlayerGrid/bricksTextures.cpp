#include "interface/currentGrid/onePlayerGrid/bricksTextures.h"
#include "interface/currentGrid/onePlayerGrid/brickData.h"
#include "customTypes/positionTypes.h"
#include "consts/onePlayerGridConsts.h"
#include "wx/dc.h"
#include "wx/textctrl.h"
#include <fstream>
#include <algorithm>
#include <cassert>

constexpr char GenericBrickDataFilePath[] = "data/textures/editor_genericBricks.txt";
constexpr char RichBrickDataFilePath[] = "data/textures/editor_richBricks.txt";
constexpr char GiftBrickDataFilePath[] = "data/textures/editor_giftsBricks.txt";
constexpr char HardBrickDataFilePath[] = "data/textures/editor_hardBricks.txt";
constexpr char BonusBrickTexturePath[] = "textures/editor/bricks/bonusBrick_editor.png";
constexpr char IceCubeBrickTexturePath[] = "textures/editor/bricks/iceCubeBrick_editor.png";
constexpr char PinguinBrickTexturePath[] = "textures/editor/bricks/pinguinBrick_editor.png";

constexpr char HellSkullBrickTexturePath[] = "textures/editor/bricks/skullBrick_editor.png";


OnePBricksTextures::OnePBricksTextures(wxTextCtrl *logWindow):
	isLoadingPerfect{true},
	bonusBrick{ BonusBrickTexturePath, wxBITMAP_TYPE_PNG},
	iceCubeBrick{ IceCubeBrickTexturePath, wxBITMAP_TYPE_PNG},
	pinguinBrick{ PinguinBrickTexturePath, wxBITMAP_TYPE_PNG},
	hellSkullBrick{ HellSkullBrickTexturePath, wxBITMAP_TYPE_PNG}
{
	if( logWindow )
	{
		loadGenericBricks(*logWindow);
		loadRichBricks(*logWindow);
		loadGiftBricks(*logWindow);
		load10ptsBrick(*logWindow);
		loadHardBricks(*logWindow);
		loadLavaStoneBrick(*logWindow);
		checkRessourcesLoading(*logWindow);
	}
}

bool OnePBricksTextures::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

void OnePBricksTextures::drawSingleBrick(wxDC& drawContext, const BrickData& brickData, const Offset& position) const
{
	switch( brickData.index )
	{
		case bricks::index::GenericBrick:
			drawGeneric(drawContext, brickData.property, position);
			break;
		case bricks::index::RichBrick:
			drawRich(drawContext, brickData.property, position);
			break;
		case bricks::index::BonusCoin:
			drawBonusCoinBrick(drawContext, position);
			break;
		case bricks::index::GiftBrick:
			drawGiftBrick(drawContext, brickData.property, position);
			break;
		case bricks::index::TenPointsBrick:
			drawTenPtsBricks(drawContext, brickData.property, position);
			break;
		case bricks::index::SolidBrick:
			drawSolidBrick(drawContext, brickData.property, position);
			break;
		case bricks::index::IceBrick:
			drawIceBricks(drawContext, brickData.property, position);
			break;
		case bricks::index::HellBricks:
			drawHellBrick(drawContext, brickData.property, position);
			break;
	}
}

void OnePBricksTextures::drawGeneric(wxDC& drawContext, unsigned brickInfo, const Offset& position) const
{
	if( brickInfo < bricks::GenericBrick::Max )
		drawContext.DrawBitmap(generic[brickInfo], position.x, position.y, true);
}

void OnePBricksTextures::drawRich(wxDC& drawContext, unsigned brickInfo, const Offset& position) const
{
	if( brickInfo < bricks::RichBrick::Max )
		drawContext.DrawBitmap(rich[brickInfo], position.x, position.y, true);
}

void OnePBricksTextures::drawBonusCoinBrick(wxDC& drawContext, const Offset& position) const
{
	drawContext.DrawBitmap(bonusBrick, position.x, position.y, true);
}

void OnePBricksTextures::drawGiftBrick(wxDC& drawContext, unsigned brickInfo, const Offset& position) const
{
	if( brickInfo < bricks::bonuses::Max )
		drawContext.DrawBitmap(giftBricks[brickInfo], position.x, position.y, true);
}

void OnePBricksTextures::drawTenPtsBricks(wxDC& drawContext, unsigned brickInfo, const Offset& position) const
{
	if( brickInfo < TenPointsBrickStateNumber )
	{
		drawContext.DrawBitmap(tenPtsBrick[brickInfo], position.x, position.y, true);
	}
}

void OnePBricksTextures::drawSolidBrick(wxDC& drawContext, unsigned brickInfo, const Offset& position) const 
{
	if( brickInfo < hardBricks.size() )
	{
		drawContext.DrawBitmap(hardBricks[brickInfo], position.x, position.y, true);
	}
}

void OnePBricksTextures::drawIceBricks(wxDC& drawContext, unsigned brickInfo, const Offset& position) const
{
	switch( brickInfo )
	{
		case bricks::iceBricks::IceCube:
			drawIceCube(drawContext, position);
			break;
		case bricks::iceBricks::PinguinBrickTexturePath:
			drawContext.DrawBitmap(pinguinBrick, position.x, position.y, true);
			break;
	}
}

void OnePBricksTextures::drawIceCube(wxDC& drawContext, const Offset& position) const
{
	drawContext.DrawBitmap(iceCubeBrick, position.x, position.y, true);
}

void OnePBricksTextures::drawHellBrick(wxDC& drawContext, unsigned brickInfo, const Offset& position) const
{
	switch( brickInfo )
	{
		case bricks::hellBricks::SkullBrick:
			drawContext.DrawBitmap(hellSkullBrick, position.x, position.y, true);
			break;
		case bricks::hellBricks::LavaStone1:
			drawLavaStoneBrick(drawContext, 0, position);
			break;
		case bricks::hellBricks::LavaStone2:
			drawLavaStoneBrick(drawContext, 1, position);
			break;
		case bricks::hellBricks::LavaStone3:
			drawLavaStoneBrick(drawContext, 2, position);
			break;
			
	}
}

void OnePBricksTextures::drawLavaStoneBrick(wxDC& drawContext, unsigned brickIndex, const Offset& position) const
{
	assert( brickIndex < lavaStoneBricks.size() );
	drawContext.DrawBitmap(lavaStoneBricks[brickIndex], position.x, position.y, true);
}

void OnePBricksTextures::checkRessourcesLoading(wxTextCtrl& logWindow)
{
	checkGenericsBricks(logWindow);
	checkRichBricks(logWindow);
	checkBonusBrick(logWindow);
	checkTenPointsBrick(logWindow);
	checkHardBrick(logWindow);
	checkGiftBricks(logWindow);
	checkIceBricks(logWindow);
	checkHellSkullBrick(logWindow);
	checkLavaStoneBrick(logWindow);
}

void OnePBricksTextures::checkGenericsBricks(wxTextCtrl& logWindow)
{	
	if( generic.size() == bricks::GenericBrick::Max )
	{
		isLoadingPerfect = std::all_of(generic.cbegin(), generic.cend(), wxImageLoadedWithSuccess );
	}
	else{
		logWindow << "Error: the generic bricks textures number ( " << static_cast<int>( generic.size() ) << " ) doesn't match the " 
				<< bricks::GenericBrick::Max << " expected, check the following file: '" << GenericBrickDataFilePath << "' .\n"; 
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::checkRichBricks(wxTextCtrl& logWindow)
{
	if( rich.size() == bricks::RichBrick::Max )
	{
		isLoadingPerfect = std::all_of(rich.cbegin(), rich.cend(), wxImageLoadedWithSuccess );
	}
	else{
		logWindow << "Error: the rich bricks textures number ( " << static_cast<int>( rich.size() ) << " ) doesn't match the " << bricks::RichBrick::Max << " expected, check the following file: '" 
				<< RichBrickDataFilePath << "' .\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::checkBonusBrick(wxTextCtrl& logWindow)
{
	if( ! bonusBrick.IsOk() )
	{
		logWindow << "Error: couldn't load bonus brick texture for 1 player game, check the following file: '" << BonusBrickTexturePath << "' .\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::checkTenPointsBrick(wxTextCtrl& logWindow)
{
	if( tenPtsBrick.size() == TenPointsBrickStateNumber )
	{
		isLoadingPerfect = std::all_of(tenPtsBrick.cbegin(), tenPtsBrick.cend(), wxImageLoadedWithSuccess );
	}
	else{
		logWindow << "Error: the ten points brick texture number ( " << static_cast<int>( tenPtsBrick.size() ) << " ) doesn't match the " 
					<< static_cast<int>( TenPointsBrickStateNumber ) << " expected.\n"; 
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::checkHardBrick(wxTextCtrl& logWindow)
{
	if( hardBricks.size() == HardBricksNumber )
	{
		isLoadingPerfect = std::all_of(hardBricks.cbegin(), hardBricks.cend(), wxImageLoadedWithSuccess );
	}
	else{
		logWindow << "Error: the hard bricks textures number ( " << static_cast<int>( hardBricks.size() ) << " ) doesn't match the " 
				<< static_cast<int>( HardBricksNumber ) << "expected, check the following file: '"
				<< HardBrickDataFilePath << " .\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::checkGiftBricks(wxTextCtrl& logWindow)
{
	if( giftBricks.size() == bricks::bonuses::Max )
	{
		isLoadingPerfect = std::all_of(giftBricks.cbegin(), giftBricks.cend(), wxImageLoadedWithSuccess );
	}
	else{
		logWindow << "Error: the gift bricks number ( " << static_cast<int>( giftBricks.size() ) << " ) doesn't match the " << bricks::bonuses::Max << " expected, check the following file: '"
				<< GiftBrickDataFilePath << "' .\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::checkIceBricks(wxTextCtrl& logWindow)
{
	if( ! ( iceCubeBrick.IsOk() && pinguinBrick.IsOk() ) )
	{
		logWindow << "Error: couldn't load ice cube brick and/or pinguin texture for 1 player game, check the following file: '" << IceCubeBrickTexturePath 
				 << "' and the other '" << PinguinBrickTexturePath << "' file.\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::checkHellSkullBrick(wxTextCtrl& logWindow)
{
	if( ! hellSkullBrick.IsOk() )
	{
		logWindow << "Error: couldn't load the 'hell skull brick' texture for 1 player game, check the following file: '" << HellSkullBrickTexturePath << "' .\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::checkLavaStoneBrick(wxTextCtrl& logWindow)
{
	if( lavaStoneBricks.size() == LavaStoneBricksNumber )
	{
		isLoadingPerfect = std::all_of(lavaStoneBricks.cbegin(), lavaStoneBricks.cend(), wxImageLoadedWithSuccess );
	}
	else{
		logWindow << "Error: there's is not enough 'lava stone' bricks loaded: " << static_cast<int>( lavaStoneBricks.size() )<< " whereas there should be " 
					<< static_cast<int>( LavaStoneBricksNumber ) << " of them loaded.\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::loadGenericBricks(wxTextCtrl& logWindow)
{
	if( std::ifstream dataFile{ GenericBrickDataFilePath } )
	{
		std::string fileLine;
		while( std::getline(dataFile, fileLine) )
		{
			generic.emplace_back(wxImage{fileLine.c_str(), wxBITMAP_TYPE_PNG});
		}
	}
	else{
		logWindow << "Error: couldn't open '" << GenericBrickDataFilePath << "' file in order to load generic bricks textures.\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::loadRichBricks(wxTextCtrl& logWindow)
{
	if( std::ifstream dataFile{RichBrickDataFilePath} )
	{
		std::string fileLine;
		while( std::getline(dataFile, fileLine) )
		{
			rich.emplace_back(wxImage{fileLine.c_str(), wxBITMAP_TYPE_PNG});
		}
	}
	else{
		logWindow << "Error: couldn't open '" << RichBrickDataFilePath << "' file in order to load rich bricks textures.\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::loadGiftBricks(wxTextCtrl& logWindow)
{
	if( std::ifstream dataFile{GiftBrickDataFilePath} )
	{
		std::string fileLine;
		while( std::getline(dataFile, fileLine) )
		{
			giftBricks.emplace_back(wxImage{fileLine.c_str(), wxBITMAP_TYPE_PNG});
		}
	}
	else{
		logWindow << "Error: couldn't open '" << GiftBrickDataFilePath << "' file in order to load gift bricks textures.\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::load10ptsBrick(wxTextCtrl& logWindow)
{
	for( std::size_t i{0} ; i < TenPointsBrickStateNumber ; ++i )
	{
		wxString str{ "textures/editor/bricks/br10pts_editor_" };
		str << i;
		str += ".png";
		tenPtsBrick.emplace_back(wxImage{str, wxBITMAP_TYPE_PNG});
		if( ! tenPtsBrick.back().IsOk() )
		{
			isLoadingPerfect = false;
			logWindow << "Error: couldn't create '10 pts brick' wxImage.\n";
		}
	}
}

void OnePBricksTextures::loadHardBricks(wxTextCtrl& logWindow)
{
	if( std::ifstream hardBricksDataFile{HardBrickDataFilePath} )
	{
		std::string fileLine;
		while( std::getline(hardBricksDataFile, fileLine) )
		{
			hardBricks.emplace_back(wxImage{fileLine.c_str(), wxBITMAP_TYPE_PNG});
		}
	}
	else{
		logWindow << "Error: couldn't open '" << HardBrickDataFilePath << "' file in order to load hard bricks textures.\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::loadLavaStoneBrick(wxTextCtrl& logWindow)
{
	for( std::size_t i{0} ; i < LavaStoneBricksNumber ; ++i )
	{
		wxString texturePath{"textures/editor/bricks/solidLavaBrick_editor_"};
		texturePath << static_cast<int>(i) << ".png";
		lavaStoneBricks.emplace_back( wxImage{ texturePath, wxBITMAP_TYPE_PNG} );
		
		if( ! lavaStoneBricks.back().IsOk() )
		{
			logWindow << "Error: couldn't create wxImage of lava stone brick texture.\n";
			isLoadingPerfect = false;
		}
	}

}

bool wxImageLoadedWithSuccess(const wxImage& image)
{
	return image.IsOk();
}