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
	return playersInputs.wasLoadingPerfect() && rackets[duels::PlayerBlue].wasLoadingPerfect() && rackets[duels::PlayerRed].wasLoadingPerfect() 
			&& bonusGenerator[duels::PlayerBlue].wasLoadingPerfect() && bonusGenerator[duels::PlayerRed].wasLoadingPerfect() ;
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
	if( playersInputs.getInputState(playerNumber, duels::InputMoveLeft) 
		&& false == playersInputs.getInputState(playerNumber, duels::InputMoveRight) 
		&& canMoveRackToLeft )
	{
		rackets[playerNumber].moveRacket(MoveToLeft);
	}
}

void PlayersThings::moveRacketToRight(unsigned playerNumber, bool canMoveRackToRight)
{
	if( playersInputs.getInputState(playerNumber, duels::InputMoveRight) 
		&& false == playersInputs.getInputState(playerNumber, duels::InputMoveLeft) 
		&& canMoveRackToRight )
	{
		rackets[playerNumber].moveRacket(MoveToRight);
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
	rackets.emplace_back( PlayerRacket{logs, rndWnd, GameScreenHeight - SQR_SIZE - SQR_SIZE * 10 / 64, RacketIsBlue, duels::RacketDefaultSpeed} );
	rackets.emplace_back( PlayerRacket{logs, rndWnd, SQR_SIZE, RacketIsRed, duels::RacketDefaultSpeed} );
	bonusGenerator.emplace_back( BonusGenerator{logs, rndWnd, duels::PlayerBlue, levelOptions.bonuses} );
	bonusGenerator.emplace_back( BonusGenerator{logs, rndWnd, duels::PlayerRed, levelOptions.bonuses} );
	racketsSpeedGradients.emplace_back( sdl2::VerticalGradient{logs, rndWnd, static_cast<unsigned>(rackets[duels::PlayerBlue].getSpeed()-duels::RacketMinimumSpeed), 
												static_cast<unsigned>(duels::RacketMaxSpeed-duels::RacketMinimumSpeed), 
												duels::BluePlayerSpeedGradientRect, BlueColor, DarkBlueColor, true} );
	racketsSpeedGradients.emplace_back( sdl2::VerticalGradient{logs, rndWnd, static_cast<unsigned>(rackets[duels::PlayerRed].getSpeed()-duels::RacketMinimumSpeed), 
												static_cast<unsigned>(duels::RacketMaxSpeed-duels::RacketMinimumSpeed), 
												duels::RedPlayerSpeedGradientRect, RedColor, DarkRedColor, true} );
	gradientBackgrounds.emplace_back( TextureCombo{logs, rndWnd, BlackColor, duels::BluePlayerSpeedGradientRect.w, duels::BluePlayerSpeedGradientRect.h, 
													TexturePosition{duels::BluePlayerSpeedGradientRect.x, duels::BluePlayerSpeedGradientRect.y} } );
	gradientBackgrounds.emplace_back( TextureCombo{logs, rndWnd, BlackColor, duels::RedPlayerSpeedGradientRect.w, duels::RedPlayerSpeedGradientRect.h, 
													TexturePosition{duels::RedPlayerSpeedGradientRect.x, duels::RedPlayerSpeedGradientRect.y} } );
	scoresDrawing.emplace_back( duels::ScoreDraw{logs, rndWnd, arialFont, Offset{ GameScreenWidth - SQR_SIZE - SQR_SIZE / 2, GameScreenHeight - SQR_SIZE / 2}, 
													levelOptions.playersScores[duels::PlayerBlue] } );
	scoresDrawing.emplace_back( duels::ScoreDraw{logs, rndWnd, arialFont, Offset{ GameScreenWidth - SQR_SIZE - SQR_SIZE / 2, SQR_SIZE / 2},
													levelOptions.playersScores[duels::PlayerRed] } );
}
 
