#ifndef DuelsMatchEnd_INTERFACE_H
#define DuelsMatchEnd_INTERFACE_H

#include "text/sdl2ttf_font.h"
#include "texts/textLoader.h"
#include "texturing/texturesCombo.h"

struct Essentials;
namespace duels{ struct LevelOptions; }

class DuelsEndInterface
{
private:
	sdl2::Font fancyFont;
	TextsBlocks texts;
	TextureCombo noWinner;
	TextureCombo winnerIs;
	TextureCombo chocolateMedal;

public:
	explicit DuelsEndInterface(Essentials& essentials, const duels::LevelOptions& levelOptions);
	~DuelsEndInterface() = default;
	DuelsEndInterface( const DuelsEndInterface& ) = delete;
	DuelsEndInterface& operator= ( const DuelsEndInterface& ) = delete;
	DuelsEndInterface( DuelsEndInterface&& ) = default;
	DuelsEndInterface& operator= ( DuelsEndInterface&& ) = default;
	
	void drawEverything(Essentials& essentials, const duels::LevelOptions& levelOptions) const;

};

#endif //DuelsMatchEnd_INTERFACE_H