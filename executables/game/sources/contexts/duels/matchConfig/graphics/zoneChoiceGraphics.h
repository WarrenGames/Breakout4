#ifndef ZONE_CHOICE_GRAPHICS_H
#define ZONE_CHOICE_GRAPHICS_H

#include "texturing/verticalGradientTexture.h"
#include "contexts/duels/matchConfig/graphics/bonusVignettes.h"
#include "contexts/duels/matchConfig/graphics/spinAnimation.h"
#include "contexts/duels/matchConfig/graphics/zonesPanels.h"
#include "texturing/texturesCombo.h"

struct Essentials;
class TextsBlocks;
namespace duels{ struct LevelOptions; }
namespace sdl2{ class Font; }

enum{ SpinZoneSpecific, SpinBonuses, SpinOtherOptions, SpinMax };

struct ZoneChoiceGraphics
{
	const TextureCombo grad;
	const duels::BonusVignettes vignettes;
	SpinAnim spin;
	const ZonesPanels panelsTextures;
	const std::vector< SDL_Color > colors;
	const std::vector< std::string > playersStrings;
	std::vector< TextureCombo > scoresTexts;
	const std::vector< Offset > spinsCoordinates;
	bool canChangeScoreGraphics;


	explicit ZoneChoiceGraphics(Essentials& essentials, const sdl2::Font& fancyFont, const TextsBlocks& langTexts, duels::LevelOptions& levelOptions);
	~ZoneChoiceGraphics() = default;
	ZoneChoiceGraphics( const ZoneChoiceGraphics& ) = delete;
	ZoneChoiceGraphics& operator= ( const ZoneChoiceGraphics& ) = delete;
	ZoneChoiceGraphics( ZoneChoiceGraphics&& ) = default;
	ZoneChoiceGraphics& operator= ( ZoneChoiceGraphics&& ) = default;
	
	void drawEverything(Essentials& essentials, std::size_t panelIndex);
	void drawPlayerThings(Essentials& essentials) const ;
	void changeScoreGraphics(Essentials& essentials, const sdl2::Font& fancyFont, duels::LevelOptions& levelOptions);
	void setScoreUpdateFlag();
	void drawSpins(Essentials& essentials);
	bool isSpinClicked(std::size_t spinNumber, const Offset& mousePosition, bool mouseButtonState) const;
};

#endif //ZONE_CHOICE_GRAPHICS_H