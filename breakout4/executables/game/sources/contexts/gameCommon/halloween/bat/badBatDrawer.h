#ifndef DUELS_BAD_BAT_DRAWER_H
#define DUELS_BAD_BAT_DRAWER_H

#include "texturing/texturesCombo.h"
#include "contexts/gameCommon/halloween/bat/batConsts.h"
#include <array>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }
class BadBatData;

class BadBatDrawer
{
private:
	std::array< TextureCombo, bat::WING_IMG_NUMBER > batLeftWing;
	std::array< TextureCombo, bat::WING_IMG_NUMBER > batRightWing;
	std::array< TextureCombo, bat::FACE_MAX > batFaces;

public:
	explicit BadBatDrawer(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);
	~BadBatDrawer() = default;
	BadBatDrawer( const BadBatDrawer& ) = delete;
	BadBatDrawer& operator= ( const BadBatDrawer& ) = delete;
	BadBatDrawer( BadBatDrawer&& ) = default;
	BadBatDrawer& operator= ( BadBatDrawer&& ) = default;
	
	void drawBat(sdl2::RendererWindow& rndWnd, const BadBatData& badBatData);
	int getFaceHeight(const BadBatData& badBatData) const;
	bool isBatOutsideOfScreen(const BadBatData& badBatData) const;

private:
	void drawLeftWing(sdl2::RendererWindow& rndWnd, const BadBatData& badBatData);
	void drawRightWing(sdl2::RendererWindow& rndWnd, const BadBatData& badBatData);
	void drawFace(sdl2::RendererWindow& rndWnd, const BadBatData& badBatData);
	int getLeftWingPosition(const BadBatData& badBatData) const;
	int getRightWingPosition(const BadBatData& badBatData) const;
	int get_y_position(const BadBatData& badBatData) const;
	
};

#endif //DUELS_BAD_BAT_DRAWER_H