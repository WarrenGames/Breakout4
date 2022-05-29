#ifndef DUELS_BONUS_VIGNETTES_H
#define DUELS_BONUS_VIGNETTES_H

#include "texturing/texturesCombo.h"
#include "contexts/duels/duelsConstexpr.h"
#include <array>

struct AppLogFiles;

namespace duels{

class BonusVignettes
{
private:
	std::array<TextureCombo, duels::DB_MAX> vignettes;
	
public:
	explicit BonusVignettes(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);
	~BonusVignettes() = default;
	BonusVignettes( const BonusVignettes& ) = delete;
	BonusVignettes& operator= ( const BonusVignettes& ) = delete;
	BonusVignettes( BonusVignettes&& ) = default;
	BonusVignettes& operator= ( BonusVignettes&& ) = default;
	
	void setVignettesCoordinates();
	void drawVignettes(sdl2::RendererWindow& rndWnd) const;
};

}

#endif //DUELS_BONUS_VIGNETTES_H