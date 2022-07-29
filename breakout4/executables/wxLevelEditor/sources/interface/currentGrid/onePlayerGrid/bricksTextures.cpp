#include "interface/currentGrid/onePlayerGrid/bricksTextures.h"
#include "interface/currentGrid/onePlayerGrid/brickData.h"
#include "customTypes/positionTypes.h"
#include "consts/onePlayerGridConsts.h"
#include "wx/dc.h"
#include "wx/textctrl.h"
#include <fstream>
#include <algorithm>
#include <cassert>

constexpr char GEN_BRICK_DATA_FILE_PATH[] = "data/textures/editor_genericBricks.txt";
constexpr char RICH_BRICK_DATA_FILE_PATH[] = "data/textures/editor_richBricks.txt";
constexpr char GIFT_BRICK_DATA_FILE_PATH[] = "data/textures/editor_giftsBricks.txt";
constexpr char HARD_BRICKS_DATA_FILE_PATH[] = "data/textures/editor_hardBricks.txt";
constexpr char BONUS_BRICK_TEXTURE_PATH[] = "textures/editor/bricks/bonusBrick_editor.png";
constexpr char ICE_CUBE_BRICK_TEXTURE_PATH[] = "textures/editor/bricks/iceCubeBrick_editor.png";
constexpr char PINGUIN_BRICK[] = "textures/editor/bricks/pinguinBrick_editor.png";

constexpr char HELL_SKULL_BRICK_TEXTURE_PATH[] = "textures/editor/bricks/skullBrick_editor.png";


OnePBricksTextures::OnePBricksTextures(wxTextCtrl *logWindow):
	isLoadingPerfect{true},
	bonusBrick{ BONUS_BRICK_TEXTURE_PATH, wxBITMAP_TYPE_PNG},
	iceCubeBrick{ ICE_CUBE_BRICK_TEXTURE_PATH, wxBITMAP_TYPE_PNG},
	pinguinBrick{ PINGUIN_BRICK, wxBITMAP_TYPE_PNG},
	hellSkullBrick{ HELL_SKULL_BRICK_TEXTURE_PATH, wxBITMAP_TYPE_PNG}
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
		case BRICKS::INDEX::GEN_BRICK:
			drawGeneric(drawContext, brickData.property, position);
			break;
		case BRICKS::INDEX::RICH_BRICK:
			drawRich(drawContext, brickData.property, position);
			break;
		case BRICKS::INDEX::BONUS_COIN:
			drawBonusCoinBrick(drawContext, position);
			break;
		case BRICKS::INDEX::GIFT_BRICK:
			drawGiftBrick(drawContext, brickData.property, position);
			break;
		case BRICKS::INDEX::TEN_POINTS:
			drawTenPtsBricks(drawContext, brickData.property, position);
			break;
		case BRICKS::INDEX::SOLID:
			drawSolidBrick(drawContext, brickData.property, position);
			break;
		case BRICKS::INDEX::ICE_BRICKS:
			drawIceBricks(drawContext, brickData.property, position);
			break;
		case BRICKS::INDEX::HELL_BRICKS:
			drawHellBrick(drawContext, brickData.property, position);
			break;
	}
}

void OnePBricksTextures::drawGeneric(wxDC& drawContext, unsigned brickInfo, const Offset& position) const
{
	if( brickInfo < BRICKS::GENERIC::MAX )
		drawContext.DrawBitmap(generic[brickInfo], position.x, position.y, true);
}

void OnePBricksTextures::drawRich(wxDC& drawContext, unsigned brickInfo, const Offset& position) const
{
	if( brickInfo < BRICKS::RICH::MAX )
		drawContext.DrawBitmap(rich[brickInfo], position.x, position.y, true);
}

void OnePBricksTextures::drawBonusCoinBrick(wxDC& drawContext, const Offset& position) const
{
	drawContext.DrawBitmap(bonusBrick, position.x, position.y, true);
}

void OnePBricksTextures::drawGiftBrick(wxDC& drawContext, unsigned brickInfo, const Offset& position) const
{
	if( brickInfo < BRICKS::BONUSES::MAX )
		drawContext.DrawBitmap(giftBricks[brickInfo], position.x, position.y, true);
}

void OnePBricksTextures::drawTenPtsBricks(wxDC& drawContext, unsigned brickInfo, const Offset& position) const
{
	if( brickInfo < TENPTS_BRICK_NUM )
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
		case BRICKS::ICE_BR::ICE_CUBE:
			drawIceCube(drawContext, position);
			break;
		case BRICKS::ICE_BR::PINGUIN_BRICK:
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
		case BRICKS::HELL_BR::SKULL_BRICK:
			drawContext.DrawBitmap(hellSkullBrick, position.x, position.y, true);
			break;
		case BRICKS::HELL_BR::LAVA_STONE_1:
			drawLavaStoneBrick(drawContext, 0, position);
			break;
		case BRICKS::HELL_BR::LAVA_STONE_2:
			drawLavaStoneBrick(drawContext, 1, position);
			break;
		case BRICKS::HELL_BR::LAVA_STONE_3:
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
	if( generic.size() == BRICKS::GENERIC::MAX )
	{
		isLoadingPerfect = std::all_of(generic.cbegin(), generic.cend(), wxImageLoadedWithSuccess );
	}
	else{
		logWindow << "Error: the generic bricks textures number ( " << static_cast<int>( generic.size() ) << " ) doesn't match the " 
				<< BRICKS::GENERIC::MAX << " expected, check the following file: '" << GEN_BRICK_DATA_FILE_PATH << "' .\n"; 
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::checkRichBricks(wxTextCtrl& logWindow)
{
	if( rich.size() == BRICKS::RICH::MAX )
	{
		isLoadingPerfect = std::all_of(rich.cbegin(), rich.cend(), wxImageLoadedWithSuccess );
	}
	else{
		logWindow << "Error: the rich bricks textures number ( " << static_cast<int>( rich.size() ) << " ) doesn't match the " << BRICKS::RICH::MAX << " expected, check the following file: '" 
				<< RICH_BRICK_DATA_FILE_PATH << "' .\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::checkBonusBrick(wxTextCtrl& logWindow)
{
	if( ! bonusBrick.IsOk() )
	{
		logWindow << "Error: couldn't load bonus brick texture for 1 player game, check the following file: '" << BONUS_BRICK_TEXTURE_PATH << "' .\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::checkTenPointsBrick(wxTextCtrl& logWindow)
{
	if( tenPtsBrick.size() == TENPTS_BRICK_NUM )
	{
		isLoadingPerfect = std::all_of(tenPtsBrick.cbegin(), tenPtsBrick.cend(), wxImageLoadedWithSuccess );
	}
	else{
		logWindow << "Error: the ten points brick texture number ( " << static_cast<int>( tenPtsBrick.size() ) << " ) doesn't match the " 
					<< static_cast<int>( TENPTS_BRICK_NUM ) << " expected.\n"; 
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::checkHardBrick(wxTextCtrl& logWindow)
{
	if( hardBricks.size() == HARD_BRICKS_NUM )
	{
		isLoadingPerfect = std::all_of(hardBricks.cbegin(), hardBricks.cend(), wxImageLoadedWithSuccess );
	}
	else{
		logWindow << "Error: the hard bricks textures number ( " << static_cast<int>( hardBricks.size() ) << " ) doesn't match the " 
				<< static_cast<int>( HARD_BRICKS_NUM ) << "expected, check the following file: '"
				<< HARD_BRICKS_DATA_FILE_PATH << " .\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::checkGiftBricks(wxTextCtrl& logWindow)
{
	if( giftBricks.size() == BRICKS::BONUSES::MAX )
	{
		isLoadingPerfect = std::all_of(giftBricks.cbegin(), giftBricks.cend(), wxImageLoadedWithSuccess );
	}
	else{
		logWindow << "Error: the gift bricks number ( " << static_cast<int>( giftBricks.size() ) << " ) doesn't match the " << BRICKS::BONUSES::MAX << " expected, check the following file: '"
				<< GIFT_BRICK_DATA_FILE_PATH << "' .\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::checkIceBricks(wxTextCtrl& logWindow)
{
	if( ! ( iceCubeBrick.IsOk() && pinguinBrick.IsOk() ) )
	{
		logWindow << "Error: couldn't load ice cube brick and/or pinguin texture for 1 player game, check the following file: '" << ICE_CUBE_BRICK_TEXTURE_PATH 
				 << "' and the other '" << PINGUIN_BRICK << "' file.\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::checkHellSkullBrick(wxTextCtrl& logWindow)
{
	if( ! hellSkullBrick.IsOk() )
	{
		logWindow << "Error: couldn't load the 'hell skull brick' texture for 1 player game, check the following file: '" << HELL_SKULL_BRICK_TEXTURE_PATH << "' .\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::checkLavaStoneBrick(wxTextCtrl& logWindow)
{
	if( lavaStoneBricks.size() == LAVA_STONE_BRICKS_NUM )
	{
		isLoadingPerfect = std::all_of(lavaStoneBricks.cbegin(), lavaStoneBricks.cend(), wxImageLoadedWithSuccess );
	}
	else{
		logWindow << "Error: there's is not enough 'lava stone' bricks loaded: " << static_cast<int>( lavaStoneBricks.size() )<< " whereas there should be " 
					<< static_cast<int>( LAVA_STONE_BRICKS_NUM ) << " of them loaded.\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::loadGenericBricks(wxTextCtrl& logWindow)
{
	if( std::ifstream dataFile{ GEN_BRICK_DATA_FILE_PATH } )
	{
		std::string fileLine;
		while( std::getline(dataFile, fileLine) )
		{
			generic.emplace_back(wxImage{fileLine.c_str(), wxBITMAP_TYPE_PNG});
		}
	}
	else{
		logWindow << "Error: couldn't open '" << GEN_BRICK_DATA_FILE_PATH << "' file in order to load generic bricks textures.\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::loadRichBricks(wxTextCtrl& logWindow)
{
	if( std::ifstream dataFile{RICH_BRICK_DATA_FILE_PATH} )
	{
		std::string fileLine;
		while( std::getline(dataFile, fileLine) )
		{
			rich.emplace_back(wxImage{fileLine.c_str(), wxBITMAP_TYPE_PNG});
		}
	}
	else{
		logWindow << "Error: couldn't open '" << RICH_BRICK_DATA_FILE_PATH << "' file in order to load rich bricks textures.\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::loadGiftBricks(wxTextCtrl& logWindow)
{
	if( std::ifstream dataFile{GIFT_BRICK_DATA_FILE_PATH} )
	{
		std::string fileLine;
		while( std::getline(dataFile, fileLine) )
		{
			giftBricks.emplace_back(wxImage{fileLine.c_str(), wxBITMAP_TYPE_PNG});
		}
	}
	else{
		logWindow << "Error: couldn't open '" << GIFT_BRICK_DATA_FILE_PATH << "' file in order to load gift bricks textures.\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::load10ptsBrick(wxTextCtrl& logWindow)
{
	for( std::size_t i{0} ; i < TENPTS_BRICK_NUM ; ++i )
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
	if( std::ifstream hardBricksDataFile{HARD_BRICKS_DATA_FILE_PATH} )
	{
		std::string fileLine;
		while( std::getline(hardBricksDataFile, fileLine) )
		{
			hardBricks.emplace_back(wxImage{fileLine.c_str(), wxBITMAP_TYPE_PNG});
		}
	}
	else{
		logWindow << "Error: couldn't open '" << HARD_BRICKS_DATA_FILE_PATH << "' file in order to load hard bricks textures.\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::loadLavaStoneBrick(wxTextCtrl& logWindow)
{
	for( std::size_t i{0} ; i < LAVA_STONE_BRICKS_NUM ; ++i )
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