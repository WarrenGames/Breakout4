#ifndef DUELS_BONUS_DRAWER_H
#define DUELS_BONUS_DRAWER_H

#include "advancedDrawing/texturesLoading/fileTexturesList.h"
#include "advancedDrawing/texturesDrawing/constAnimationDrawing.h"

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }

class BonusDrawer
{
private:
	TexturesFilesList loadedTextures;
	ConstAnimDraw draw;
	
public:
	BonusDrawer(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned playerType);
	~BonusDrawer() = default;
	BonusDrawer( const BonusDrawer& ) = delete;
	BonusDrawer& operator= ( BonusDrawer& ) = delete;
	BonusDrawer( BonusDrawer&& ) = default;
	BonusDrawer& operator= ( BonusDrawer&& ) = default;
	
	bool wasLoadingPerfect() const;
	
	void drawBonus(sdl2::RendererWindow& rndWnd, unsigned bonusNumber) const;

private:
	void setTexturesPositions(unsigned playerType);
};

#endif //DUELS_BONUS_DRAWER_H