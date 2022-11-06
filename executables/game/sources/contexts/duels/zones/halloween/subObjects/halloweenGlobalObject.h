#ifndef DUELS_HALLOWEEN_GLOBAL_OBJECT_H
#define DUELS_HALLOWEEN_GLOBAL_OBJECT_H

#include "contexts/duels/zones/halloween/subObjects/halloweenArea.h"
#include "contexts/duels/zones/halloween/subObjects/halloweenFactory.h"
#include "contexts/duels/inGameObjects/global/duelsGlobalObject.h"
#include "text/sdl2ttf_font.h"
#include "consts/fontsConsts.h"
#include "time/accurateTime.h"

struct Essentials;

namespace duels{

struct HalloweenPack
{
	const sdl2::Font arial;
	duels::HalloweenFactory factory;
	duels::HalloweenArea area;
	duels::GlobalObject zonesCommon;
	const TextureCombo nightWallpaper;
	const TextureCombo daytimeWallpaper;

	HalloweenPack(Essentials& essentials, const duels::LevelOptions& levelOptions);
	~HalloweenPack() = default;
	HalloweenPack( const HalloweenPack& ) = delete;
	HalloweenPack& operator= ( const HalloweenPack& ) = delete;
	HalloweenPack( HalloweenPack&& ) = default;
	HalloweenPack& operator= ( HalloweenPack&& ) = default;

	bool wasLoadingPerfect() const;

	void update(Essentials& essentials, duels::LevelOptions& levelOptions, bool& quitZone);

	void drawWallpaper(Essentials& essentials, const duels::LevelOptions& levelOptions) const;

	void drawEverything(Essentials& essentials, const duels::LevelOptions& levelOptions);
	
	void activateSpecificFlagIfAny(const duels::LevelOptions& levelOptions);
};

}

#endif //DUELS_HALLOWEEN_GLOBAL_OBJECT_H