#ifndef MET_STRINGS_GLOBAL_SPECIFIC_OBJECT_H
#define MET_STRINGS_GLOBAL_SPECIFIC_OBJECT_H

#include "duels/inGameObjects/global/duelsGlobalObject.h"
#include "duels/zones/metalStrings/subObjects/stringDrawer.h"
#include "duels/zones/metalStrings/subObjects/verticalBarriersDrawing.h"
#include "duels/zones/metalStrings/subObjects/notStringsElements.h"
#include "duels/zones/metalStrings/subObjects/switchsData.h"
#include "duels/zones/metalStrings/subObjects/barriersData.h"
#include "duels/zones/metalStrings/subObjects/steamPipe.h"

namespace duels{

struct MetalStrings
{
	duels::GlobalObject zonesCommon;
	metalStrings::StringsDrawer stringDrawer;
	VerticalBarrierDrawing inWayBarriers;
	metalStrings::LevelBricks bricks;
	metalStrings::SwitchsData switchData;
	BarriersData barriersData;
	SteamPipe steamPipe; 
	
	explicit MetalStrings(Essentials& essentials, const sdl2::Font& arial, duels::LevelOptions& levelOptions);
	~MetalStrings() = default;
	MetalStrings( const MetalStrings& ) = delete;
	MetalStrings& operator= ( const MetalStrings& ) = delete;
	MetalStrings( MetalStrings&& ) = default;
	MetalStrings& operator= ( MetalStrings&& ) = default;
	
	operator bool () const;
	
	void update(Essentials& essentials, const sdl2::Font& arial, duels::LevelOptions& levelOptions, bool& quitZone);
	void drawEverything(Essentials& essentials);
	
	void activateBarriersWithInputs();
	void moveBarrier(unsigned playerNum, unsigned directionType);
	void updateTopBarrier();
	void updateBottomBarrier();
	void moveUpBarrier(std::size_t playerNum);
	void moveDownBarrier(std::size_t playerNum);
	void checkBarriersPositions(std::size_t playerNum, bool barrierPrevent, bool barrierInInitialPosition);
	void testBarrierWithBallsAndCoinsCollisions();
	void makeTopBarrierRegressDueToRacketInWay();
	void makeBottomBarrierRegressDueToRacketInWay();
};

}

namespace metalStrings{
	
bool isRacketInWayOfBarrier(const SDL_Rect& racket, const SDL_Rect& barrier);

bool isBlueRacketLeftNotBlockedByBarrier(const SDL_Rect& racket, const SDL_Rect& barrier);

bool isBlueRacketRightNotBlockedByBarrier(const SDL_Rect& racket, const SDL_Rect& barrier);

bool isRedRacketLeftNotBlockedByBarrier(const SDL_Rect& racket, const SDL_Rect& barrier);

bool isRedRacketRightNotBlockedByBarrier(const SDL_Rect& racket, const SDL_Rect& barrier);

}

#endif //MET_STRINGS_GLOBAL_SPECIFIC_OBJECT_H