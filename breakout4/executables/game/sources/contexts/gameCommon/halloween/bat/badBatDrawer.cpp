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
	return sprites[bat::TEXTURE_FACES][badBatData.faceIndex].height();
}

bool BadBatDrawer::isBatOutsideOfScreen(const BadBatData& badBatData) const
{
	return false == doesRectsCollide(SDL_Rect{0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT}, 
							SDL_Rect{getLeftWingPosition(badBatData), get_y_position(badBatData), 
									sprites[bat::TEXTURE_LEFT_WING][badBatData.wingsFrameNumber].width() + sprites[bat::TEXTURE_FACES][badBatData.faceIndex].width()
									+ sprites[bat::TEXTURE_RIGHT_WING][badBatData.wingsFrameNumber].width(),
									sprites[bat::TEXTURE_FACES][badBatData.faceIndex].height() } );
}

void BadBatDrawer::drawLeftWing(sdl2::RendererWindow& rndWnd, const BadBatData& badBatData)
{
	sprites[bat::TEXTURE_LEFT_WING][badBatData.wingsFrameNumber].draw(rndWnd, getLeftWingPosition(badBatData), get_y_position(badBatData) );
}

void BadBatDrawer::drawRightWing(sdl2::RendererWindow& rndWnd, const BadBatData& badBatData)
{
	sprites[bat::TEXTURE_RIGHT_WING][badBatData.wingsFrameNumber].draw(rndWnd, getRightWingPosition(badBatData), get_y_position(badBatData) );
}

void BadBatDrawer::drawFace(sdl2::RendererWindow& rndWnd, const BadBatData& badBatData)
{
	sprites[bat::TEXTURE_FACES][badBatData.faceIndex].drawToCenter(rndWnd, badBatData.batMove.get_x_position(), badBatData.batMove.get_y_position() );
}

int BadBatDrawer::getLeftWingPosition(const BadBatData& badBatData) const
{
	return badBatData.batMove.get_x_position() - sprites[bat::TEXTURE_FACES][badBatData.faceIndex].width() / 2 + bat::DIST_WINGS_FROM_FACE_W
		- sprites[bat::TEXTURE_LEFT_WING][badBatData.wingsFrameNumber].width() + badBatData.getOffset().x;
}

int BadBatDrawer::getRightWingPosition(const BadBatData& badBatData) const
{
	return badBatData.batMove.get_x_position() + sprites[bat::TEXTURE_FACES][badBatData.faceIndex].width() / 2 - bat::DIST_WINGS_FROM_FACE_W - badBatData.getOffset().x;
}

int BadBatDrawer::get_y_position(const BadBatData& badBatData) const
{
	return badBatData.batMove.get_y_position()
			- sprites[bat::TEXTURE_FACES][badBatData.faceIndex].height() / 2
			+ bat::DIST_WINGS_FROM_FACE_H 
			- badBatData.getOffset().y;
}

void BadBatDrawer::loadTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd)
{
	loadedTextures.emplace_back( TexturesFilesList{logs, rndWnd, "data/textures/batLeftWingTextures.txt"} );
	loadedTextures.emplace_back( TexturesFilesList{logs, rndWnd, "data/textures/batRightWingTextures.txt"} );
	loadedTextures.emplace_back( TexturesFilesList{logs, rndWnd, "data/textures/batFacesTextures.txt"} );
	assert( loadedTextures.size() == bat::TEXTURE_MAX );
	
	for( auto const &loadTex : loadedTextures )
	{
		sprites.emplace_back( ConstAnimDraw{loadTex} );
	}
}