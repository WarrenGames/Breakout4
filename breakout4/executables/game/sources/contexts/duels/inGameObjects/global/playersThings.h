#ifndef DUELS_PLAYERS_THINGS_H
#define DUELS_PLAYERS_THINGS_H

#include "contexts/duels/inGameObjects/rackets/racket.h"
#include "contexts/duels/inGameObjects/bonus/bonusGenerator.h"
#include "texturing/verticalGradientTexture.h"
#include "contexts/duels/inGameObjects/playerScore/playerScoreDrawing.h"
#include "contexts/duels/inGameObjects/playerInputs/playersInputs.h"
#include "contexts/duels/inGameObjects/gameElements/duelsTypes.h"
#include <array>

struct AppLogFiles;
class PrefPathFinder;
namespace sdl2{ class RendererWindow; }

struct PlayersThings
{
	std::array< PlayerRacket, duels::PLAYER_MAX > rackets;
	std::array< BonusGenerator, duels::PLAYER_MAX > bonusGenerator;
	std::array< sdl2::VerticalGradient, duels::PLAYER_MAX > racketsSpeedGradients;
	std::array< TextureCombo, duels::PLAYER_MAX > gradientBackgrounds;
	std::array< duels::ScoreDraw, duels::PLAYER_MAX > scoresDrawing;
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
};

#endif //DUELS_PLAYERS_THINGS_H