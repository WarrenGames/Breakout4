#ifndef DUELS_BONUS_VIGNETTES_H
#define DUELS_BONUS_VIGNETTES_H

#include "advancedDrawing/texturesLoading/fileTexturesList.h"
#include "advancedDrawing/texturesDrawing/constAnimationDrawing.h"

struct AppLogFiles;

namespace duels{

class BonusVignettes
{
private:
	TexturesFilesList loadedTextures;
	ConstAnimDraw draw;
	
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