#ifndef ONE_PLAYER_BONUSES_COUNT_GRAPHICS_H
#define ONE_PLAYER_BONUSES_COUNT_GRAPHICS_H

#include "texturing/texturesCombo.h"
#include "text/sdl2ttf_font.h"
#include "consts/fontsConsts.h"
#include <vector>

struct Essentials;
struct PlayerData;
class BagIconsTextures;

class BonusesCountGraphics
{
private:
	bool isLoadingPerfect;
	sdl2::Font fancyFont;
	std::vector< TextureCombo > bonusesCount;
	std::vector< bool > updateTexts;
	
public:
	explicit BonusesCountGraphics(Essentials& essentials);
	~BonusesCountGraphics() = default;
	BonusesCountGraphics( const BonusesCountGraphics& ) = delete;
	BonusesCountGraphics& operator= ( const BonusesCountGraphics& ) = delete;
	BonusesCountGraphics( BonusesCountGraphics&& ) = default;
	BonusesCountGraphics& operator= ( BonusesCountGraphics&& ) = default;
	
	void drawEverything(Essentials& essentials) const;
	
	void setUpdateFlag(std::size_t bonusNumber);
	void updateNeededTexts(Essentials& essentials, const PlayerData& playerData, const std::vector<TextureCombo>& bagIcons);
};

#endif //ONE_PLAYER_BONUSES_COUNT_GRAPHICS_H