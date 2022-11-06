#include "contexts/gameCommon/halloween/bat/badBatDrawer.h"
#include "contexts/gameCommon/halloween/bat/badBatData.h"
#include "contexts/duels/instructions/positionCheck.h"
#include "contexts/gameCommon/halloween/bat/batConsts.h"
#include "consts/constexprScreen.h"
#include <cassert>

BadBatDrawer::BadBatDrawer(AppLogFiles& logs, sdl2::RendererWindow& rndWnd)
{
	loadTextures(logs, rndWnd);
}

void BadBatDrawer::drawBat(sdl2::RendererWindow& rndWnd, const BadBatData& badBatData)
{
	drawLeftWing(rndWnd, badBatData);
	drawRightWing(rndWnd ,badBatData);
	drawFace(rndWnd, badBatData);
}

int BadBatDrawer::getFaceHeight(const BadBatData& badBatData) const
{
	return sprites[bat::TextureFaces][badBatData.faceIndex].height();
}

bool BadBatDrawer::isBatOutsideOfScreen(const BadBatData& badBatData) const
{
	return false == doesRectsCollide(SDL_Rect{0, 0, GameScreenWidth, GameScreenHeight}, 
							SDL_Rect{getLeftWingPosition(badBatData), get_y_position(badBatData), 
									sprites[bat::TextureLeftWing][badBatData.wingsFrameNumber].width() + sprites[bat::TextureFaces][badBatData.faceIndex].width()
									+ sprites[bat::TextureRightWing][badBatData.wingsFrameNumber].width(),
									sprites[bat::TextureFaces][badBatData.faceIndex].height() } );
}

void BadBatDrawer::drawLeftWing(sdl2::RendererWindow& rndWnd, const BadBatData& badBatData)
{
	sprites[bat::TextureLeftWing][badBatData.wingsFrameNumber].draw(rndWnd, getLeftWingPosition(badBatData), get_y_position(badBatData) );
}

void BadBatDrawer::drawRightWing(sdl2::RendererWindow& rndWnd, const BadBatData& badBatData)
{
	sprites[bat::TextureRightWing][badBatData.wingsFrameNumber].draw(rndWnd, getRightWingPosition(badBatData), get_y_position(badBatData) );
}

void BadBatDrawer::drawFace(sdl2::RendererWindow& rndWnd, const BadBatData& badBatData)
{
	sprites[bat::TextureFaces][badBatData.faceIndex].drawToCenter(rndWnd, badBatData.batMove.get_x_position(), badBatData.batMove.get_y_position() );
}

int BadBatDrawer::getLeftWingPosition(const BadBatData& badBatData) const
{
	return badBatData.batMove.get_x_position() - sprites[bat::TextureFaces][badBatData.faceIndex].width() / 2 + bat::WingsFromFaceDistanceWidth
		- sprites[bat::TextureLeftWing][badBatData.wingsFrameNumber].width() + badBatData.getOffset().x;
}

int BadBatDrawer::getRightWingPosition(const BadBatData& badBatData) const
{
	return badBatData.batMove.get_x_position() + sprites[bat::TextureFaces][badBatData.faceIndex].width() / 2 - bat::WingsFromFaceDistanceWidth - badBatData.getOffset().x;
}

int BadBatDrawer::get_y_position(const BadBatData& badBatData) const
{
	return badBatData.batMove.get_y_position()
			- sprites[bat::TextureFaces][badBatData.faceIndex].height() / 2
			+ bat::WingsFromFaceDistanceHeight 
			- badBatData.getOffset().y;
}

void BadBatDrawer::loadTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd)
{
	loadedTextures.emplace_back( TexturesFilesList{logs, rndWnd, "data/textures/batLeftWingTextures.txt"} );
	loadedTextures.emplace_back( TexturesFilesList{logs, rndWnd, "data/textures/batRightWingTextures.txt"} );
	loadedTextures.emplace_back( TexturesFilesList{logs, rndWnd, "data/textures/batFacesTextures.txt"} );
	assert( loadedTextures.size() == bat::TextureMax );
	
	for( auto const &loadTex : loadedTextures )
	{
		sprites.emplace_back( ConstAnimDraw{loadTex} );
	}
}