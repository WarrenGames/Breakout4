#include "contexts/gameCommon/halloween/bat/badBatDrawer.h"
#include "contexts/gameCommon/halloween/bat/badBatData.h"
#include "contexts/duels/instructions/positionCheck.h"
#include "consts/constexprScreen.h"

BadBatDrawer::BadBatDrawer(AppLogFiles& logs, sdl2::RendererWindow& rndWnd):
	batLeftWing{
		TextureCombo{logs, rndWnd, "textures/sprites/bat/wing_left0.png"},
		TextureCombo{logs, rndWnd, "textures/sprites/bat/wing_left1.png"},
		TextureCombo{logs, rndWnd, "textures/sprites/bat/wing_left2.png"},
		TextureCombo{logs, rndWnd, "textures/sprites/bat/wing_left3.png"},
		TextureCombo{logs, rndWnd, "textures/sprites/bat/wing_left4.png"},
	},
	batRightWing{
		TextureCombo{logs, rndWnd, "textures/sprites/bat/wing_right0.png"},
		TextureCombo{logs, rndWnd, "textures/sprites/bat/wing_right1.png"},
		TextureCombo{logs, rndWnd, "textures/sprites/bat/wing_right2.png"},
		TextureCombo{logs, rndWnd, "textures/sprites/bat/wing_right3.png"},
		TextureCombo{logs, rndWnd, "textures/sprites/bat/wing_right4.png"}
	},
	batFaces{
		TextureCombo{logs, rndWnd, "textures/sprites/bat/bat_effort.png"},
		TextureCombo{logs, rndWnd, "textures/sprites/bat/bat_disapoint.png"},
		TextureCombo{logs, rndWnd, "textures/sprites/bat/bat_happy.png"}
	}
{
	
}

void BadBatDrawer::drawBat(sdl2::RendererWindow& rndWnd, const BadBatData& badBatData)
{
	drawLeftWing(rndWnd, badBatData);
	drawRightWing(rndWnd ,badBatData);
	drawFace(rndWnd, badBatData);
}

int BadBatDrawer::getFaceHeight(const BadBatData& badBatData) const
{
	return batFaces[badBatData.faceIndex].sprite.height();
}

bool BadBatDrawer::isBatOutsideOfScreen(const BadBatData& badBatData) const
{
	return false == doesRectsCollide(SDL_Rect{0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT}, 
							SDL_Rect{getLeftWingPosition(badBatData), get_y_position(badBatData), 
									 batLeftWing[badBatData.wingsFrameNumber].sprite.width() + batFaces[badBatData.faceIndex].sprite.width() 
										+ batRightWing[badBatData.wingsFrameNumber].sprite.width(), 
									 batFaces[badBatData.faceIndex].sprite.width()} );
}

void BadBatDrawer::drawLeftWing(sdl2::RendererWindow& rndWnd, const BadBatData& badBatData)
{
	batLeftWing[badBatData.wingsFrameNumber].draw(rndWnd, getLeftWingPosition(badBatData), get_y_position(badBatData) );
}

void BadBatDrawer::drawRightWing(sdl2::RendererWindow& rndWnd, const BadBatData& badBatData)
{
	batRightWing[badBatData.wingsFrameNumber].draw(rndWnd, getRightWingPosition(badBatData), get_y_position(badBatData) );
}

void BadBatDrawer::drawFace(sdl2::RendererWindow& rndWnd, const BadBatData& badBatData)
{
	batFaces[badBatData.faceIndex].drawToCenter(rndWnd, badBatData.batMove.get_x_position(), badBatData.batMove.get_y_position());
}

int BadBatDrawer::getLeftWingPosition(const BadBatData& badBatData) const
{
	return badBatData.batMove.get_x_position() - batFaces[badBatData.faceIndex].sprite.width() / 2 + bat::DIST_WINGS_FROM_FACE_W - batLeftWing[badBatData.wingsFrameNumber].sprite.width() + badBatData.getOffset().x;
}

int BadBatDrawer::getRightWingPosition(const BadBatData& badBatData) const
{
	return badBatData.batMove.get_x_position() + batFaces[badBatData.faceIndex].sprite.width() / 2 - bat::DIST_WINGS_FROM_FACE_W - badBatData.getOffset().x;
}

int BadBatDrawer::get_y_position(const BadBatData& badBatData) const
{
	return badBatData.batMove.get_y_position() - batFaces[badBatData.faceIndex].sprite.height() / 2 + bat::DIST_WINGS_FROM_FACE_H - badBatData.getOffset().y;
}