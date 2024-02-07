#ifndef DUELS_RAQUETTE_H
#define DUELS_RAQUETTE_H

#include "rackets/racketDrawer.h"
#include "rackets/racketData.h"

class PlayerRacket
{
private:
	RacketDrawer drawer;
	RacketData data;
	SDL_Rect rect;

public:
	explicit PlayerRacket(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, int start_y_position, unsigned playerType, double startSpeed);
	~PlayerRacket() = default;
	PlayerRacket( const PlayerRacket& ) = delete;
	PlayerRacket& operator= ( const PlayerRacket& ) = delete;
	PlayerRacket( PlayerRacket&& ) = default;
	PlayerRacket& operator= ( PlayerRacket&& ) = default;
	
	bool wasLoadingPerfect() const;
	void drawRacket(sdl2::RendererWindow& rndWnd);
	void setRacketRect();
	void moveRacket(unsigned moveDirection);
	const SDL_Rect& getRacketRect() const;
	
	bool canBeEnlarged() const;
	void enlarge();
	
	bool canBeShrinked() const;
	void shrink();
	
	unsigned getSize() const;
	
	void changeSpeed(double addToSpeed);
	bool canBeSlowedDown() const;
	bool canSpeedUp() const;
	double getSpeed() const;
	
	void updateFreezeState();
	bool canBeFreeze() const;
	void freezeRacket();
};

#endif //DUELS_RAQUETTE_H