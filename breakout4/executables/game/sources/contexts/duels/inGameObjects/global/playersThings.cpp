#include "contexts/duels/inGameObjects/global/playersThings.h"
#include "logging/logsStruct.h"
#include "texturing/texturePosition.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

PlayersThings::PlayersThings(AppLogFiles& logs, const PrefPathFinder& prefPath, sdl2::RendererWindow& rndWnd, const sdl2::Font& arialFont, const duels::LevelOptions& levelOptions):
	playersInputs{logs, prefPath}
{
	createData(logs, rndWnd, arialFont, levelOptions);
}

bool PlayersThings::wasLoadingPerfect() const
{
	return playersInputs.wasLoadingPerfect() && rackets[duels::PLAYER_BLUE].wasLoadingPerfect() && rackets[duels::PLAYER_RED].wasLoadingPerfect() 
			&& bonusGenerator[duels::PLAYER_BLUE].wasLoadingPerfect() && bonusGenerator[duels::PLAYER_RED].wasLoadingPerfect() ;
}

void PlayersThings::update(bool& quitZone)
{
	playersInputs.updateEvents();
	quitZoneAccordingToInput(quitZone);
	updateBonuses();
}

void PlayersThings::updateBonuses()
{
	for( auto &bonus : bonusGenerator )
	{
		bonus.update();
	}
}

void PlayersThings::quitZoneAccordingToInput(bool& quitZone)
{
	if( playersInputs.getEscapeState() || playersInputs.getSDLQuit() )
	{
		quitZone = true;
		playersInputs.setEscapeFalse();
	}
}

void PlayersThings::moveRacket(unsigned playerNumber, bool canMoveRacketToLeft, bool canMoveRacketToRight )
{
	moveRacketToLeft(playerNumber, canMoveRacketToLeft);
	moveRacketToRight(playerNumber, canMoveRacketToRight);
}

void PlayersThings::moveRacketToLeft(unsigned playerNumber, bool canMoveRackToLeft)
{
	if( playersInputs.getInputState(playerNumber, duels::INP_MOV_LEFT) 
		&& false == playersInputs.getInputState(playerNumber, duels::INP_MOV_RIGHT) 
		&& canMoveRackToLeft )
	{
		rackets[playerNumber].moveRacket(MOVE_TO_LEFT);
	}
}

void PlayersThings::moveRacketToRight(unsigned playerNumber, bool canMoveRackToRight)
{
	if( playersInputs.getInputState(playerNumber, duels::INP_MOV_RIGHT) 
		&& false == playersInputs.getInputState(playerNumber, duels::INP_MOV_LEFT) 
		&& canMoveRackToRight )
	{
		rackets[playerNumber].moveRacket(MOVE_TO_RIGHT);
	}
}

void PlayersThings::drawRackets(sdl2::RendererWindow& rndWnd)
{
	for( auto &rac : rackets )
		rac.drawRacket(rndWnd);
}

void PlayersThings::drawBonusVignettes(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &vignette : bonusGenerator )
		vignette.drawVignetteIfAny(rndWnd);
}

void PlayersThings::drawSpeedGradients(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &grad : racketsSpeedGradients )
		grad.draw(rndWnd);
}

void PlayersThings::drawSpeedGradientsBackground(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &background : gradientBackgrounds )
		background.draw(rndWnd);
}

void PlayersThings::drawPlayersScores(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &score : scoresDrawing )
		score.drawScore(rndWnd);
}

void PlayersThings::updateRacketsFreezeState()
{
	for( auto &racket : rackets )
		racket.updateFreezeState();
}

void PlayersThings::createData(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& arialFont, const duels::LevelOptions& levelOptions)
{
	rackets.emplace_back( PlayerRacket{logs, rndWnd, GAME_SCREEN_HEIGHT - SQR_SIZE - SQR_SIZE * 10 / 64, RACKET_IS_BLUE, duels::RACKET_DEFAULT_SPEED} );
	rackets.emplace_back( PlayerRacket{logs, rndWnd, SQR_SIZE, RACKET_IS_RED, duels::RACKET_DEFAULT_SPEED} );
	bonusGenerator.emplace_back( BonusGenerator{logs, rndWnd, duels::PLAYER_BLUE, levelOptions.bonuses} );
	bonusGenerator.emplace_back( BonusGenerator{logs, rndWnd, duels::PLAYER_RED, levelOptions.bonuses} );
	racketsSpeedGradients.emplace_back( sdl2::VerticalGradient{logs, rndWnd, static_cast<unsigned>(rackets[duels::PLAYER_BLUE].getSpeed()-duels::RACKET_MIN_SPEED), 
												static_cast<unsigned>(duels::RACKET_MAX_SPEED-duels::RACKET_MIN_SPEED), 
												duels::BLUE_SPD_GRAD_RECT, BLUE_COL, DARK_BLUE, true} );
	racketsSpeedGradients.emplace_back( sdl2::VerticalGradient{logs, rndWnd, static_cast<unsigned>(rackets[duels::PLAYER_RED].getSpeed()-duels::RACKET_MIN_SPEED), 
												static_cast<unsigned>(duels::RACKET_MAX_SPEED-duels::RACKET_MIN_SPEED), 
												duels::RED_SPD_GRAD_RECT, RED_COL, DARK_RED, true} );
	gradientBackgrounds.emplace_back( TextureCombo{logs, rndWnd, BLACK_COL, duels::BLUE_SPD_GRAD_RECT.w, duels::BLUE_SPD_GRAD_RECT.h, 
													TexturePosition{duels::BLUE_SPD_GRAD_RECT.x, duels::BLUE_SPD_GRAD_RECT.y} } );
	gradientBackgrounds.emplace_back( TextureCombo{logs, rndWnd, BLACK_COL, duels::RED_SPD_GRAD_RECT.w, duels::RED_SPD_GRAD_RECT.h, 
													TexturePosition{duels::RED_SPD_GRAD_RECT.x, duels::RED_SPD_GRAD_RECT.y} } );
	scoresDrawing.emplace_back( duels::ScoreDraw{logs, rndWnd, arialFont, Offset{ GAME_SCREEN_WIDTH - SQR_SIZE - SQR_SIZE / 2, GAME_SCREEN_HEIGHT - SQR_SIZE / 2}, 
													levelOptions.playersScores[duels::PLAYER_BLUE] } );
	scoresDrawing.emplace_back( duels::ScoreDraw{logs, rndWnd, arialFont, Offset{ GAME_SCREEN_WIDTH - SQR_SIZE - SQR_SIZE / 2, SQR_SIZE / 2},
													levelOptions.playersScores[duels::PLAYER_RED] } );
}
 
