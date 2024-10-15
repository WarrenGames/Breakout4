#ifndef ONE_PLAYER_RACKET_H
#define ONE_PLAYER_RACKET_H

#include "rackets/racketData.h"
#include "rackets/racketDrawer.h"

struct Essentials;
namespace sdl2{ class RendererWindow; }
struct PlayerData;

struct OnePlayerRacket
{
	unsigned glueLevel;
	SDL_Rect rect;
	RacketData data;
	RacketDrawer standardRacket;
	RacketDrawer stickyRacket;
	RacketDrawer frozenRacket;
	
	OnePlayerRacket(Essentials& essentials, const PlayerData& playerData);
	~OnePlayerRacket() = default;
	OnePlayerRacket( const OnePlayerRacket& ) = delete;
	OnePlayerRacket& operator= ( const OnePlayerRacket& ) = delete;
	OnePlayerRacket( OnePlayerRacket&& ) = default;
	OnePlayerRacket& operator= ( OnePlayerRacket&& ) = default;
	
	void setRacketRect();
	void drawRacket(sdl2::RendererWindow& rndWnd);
};

#endif //ONE_PLAYER_RACKET_H