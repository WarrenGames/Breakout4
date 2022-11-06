#ifndef DUELS_PLAYERS_THINGS_H
#define DUELS_PLAYERS_THINGS_H

#include "contexts/duels/inGameObjects/rackets/racket.h"
#include "contexts/duels/inGameObjects/bonus/bonusGenerator.h"
#include "texturing/verticalGradientTexture.h"
#include "contexts/duels/inGameObjects/playerScore/playerScoreDrawing.h"
#include "contexts/duels/inGameObjects/playerInputs/playersInputs.h"
#include "contexts/duels/inGameObjects/gameElements/duelsTypes.h"
#include <vector>

struct AppLogFiles;
class PrefPathFinder;
namespace sdl2{ class RendererWindow; }

struct PlayersThings
{
	std::vector< PlayerRacket > rackets;
	std::vector< BonusGenerator > bonusGenerator;
	std::vector< sdl2::VerticalGradient > racketsSpeedGradients;
	std::vector< TextureCombo > gradientBackgrounds;
	std::vector< duels::ScoreDraw > scoresDrawing;
	duels::PlayersInputs playersInputs;

	explicit PlayersThings(AppLogFiles& logs, const PrefPathFinder& prefPath, sdl2::RendererWindow& rndWnd, const sdl2::Font& arialFont, const duels::LevelOptions& levelOptions);
	~PlayersThings() = default;
	PlayersThings( const PlayersThings& ) = delete;
	PlayersThings& operator= ( const PlayersThings& ) = delete;
	PlayersThings( PlayersThings&& ) = default;
	PlayersThings& operator= ( PlayersThings&& ) = default;
	
	bool wasLoadingPerfect() const;
	
	void update(bool& quitZone);
	void updateBonuses();
	void quitZoneAccordingToInput(bool& quitZone);
	
	void moveRacket(unsigned playerNumber, bool canMoveRacketToLeft, bool canMoveRacketToRight );
	void moveRacketToLeft(unsigned playerNumber, bool canMoveRacketToLeft);
	void moveRacketToRight(unsigned playerNumber, bool canMoveRacketToRight);
	
	void drawRackets(sdl2::RendererWindow& rndWnd);
	void drawBonusVignettes(sdl2::RendererWindow& rndWnd) const;
	void drawSpeedGradients(sdl2::RendererWindow& rndWnd) const;
	void drawSpeedGradientsBackground(sdl2::RendererWindow& rndWnd) const;
	void drawPlayersScores(sdl2::RendererWindow& rndWnd) const;
	
	void updateRacketsFreezeState();
	
	void createData(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& arialFont, const duels::LevelOptions& levelOptions);
};

#endif //DUELS_PLAYERS_THINGS_H