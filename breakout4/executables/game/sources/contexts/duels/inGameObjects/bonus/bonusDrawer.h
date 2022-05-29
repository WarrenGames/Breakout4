#ifndef DUELS_BONUS_DRAWER_H
#define DUELS_BONUS_DRAWER_H

#include "texturing/texturesCombo.h"
#include "contexts/duels/duelsConstexpr.h"
#include <array>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }

class BonusDrawer
{
private:
	std::array< TextureCombo, duels::DB_MAX > textures;
	
public:
	BonusDrawer(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned playerType);
	~BonusDrawer() = default;
	BonusDrawer( const BonusDrawer& ) = delete;
	BonusDrawer& operator= ( BonusDrawer& ) = delete;
	BonusDrawer( BonusDrawer&& ) = default;
	BonusDrawer& operator= ( BonusDrawer&& ) = default;
	
	bool wasLoadingPerfect() const;
	
	void drawBonus(sdl2::RendererWindow& rndWnd, unsigned bonusNumber) const;
};

#endif //DUELS_BONUS_DRAWER_H