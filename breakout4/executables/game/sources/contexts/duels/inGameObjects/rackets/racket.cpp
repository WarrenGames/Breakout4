#include "contexts/duels/inGameObjects/rackets/racket.h"
#include "customTypes/positionTypes.h"
#include "contexts/duels/duelsConstexpr.h"
#include <cassert>

PlayerRacket::PlayerRacket(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, int start_y_position, unsigned playerType, double startSpeed):
	drawer{logs, rndWnd, playerType},
	data{duels::MEDIUM_RACKET, startSpeed, start_y_position},
	rect{data.get_x_pos() - drawer.getWidth(data.getSize()) / 2, start_y_position, drawer.getWidth(data.getSize()), drawer.getHeight(data.getSize()) }
{
	assert( playerType < duels::PLAYER_MAX );
}

bool PlayerRacket::wasLoadingPerfect() const
{
	return drawer.wasLoadingPerfect();
}

void PlayerRacket::drawRacket(sdl2::RendererWindow& rndWnd)
{
	drawer.drawRacket(rndWnd, data.getSize(), Offset{ data.get_x_pos(), data.get_y_pos() } );
}

void PlayerRacket::setRacketRect()
{
	rect.x = data.get_x_pos() - drawer.getWidth(data.getSize()) / 2;
	rect.w = drawer.getWidth(data.getSize());
	rect.h = drawer.getHeight(data.getSize());
}

void PlayerRacket::moveRacket(unsigned moveDirection)
{
	data.moveRacket(moveDirection, drawer.getWidth(data.getSize()));
	setRacketRect();
}

const SDL_Rect& PlayerRacket::getRacketRect() const
{
	return rect;
}

bool PlayerRacket::canBeEnlarged() const
{
	return data.getSize()< duels::BIG_RACKET;
}

void PlayerRacket::enlarge()
{
	data.modifySize(1);
}

bool PlayerRacket::canBeShrinked() const
{
	return data.getSize() > duels::SMALL_RACKET;
}

void PlayerRacket::shrink()
{
	data.modifySize(-1);
}

unsigned PlayerRacket::getSize() const
{
	return data.getSize();
}

void PlayerRacket::changeSpeed(double addToSpeed)
{
	data.addToSpeed(addToSpeed);
}

bool PlayerRacket::canBeSlowedDown() const
{
	return data.getSpeed() > duels::RACKET_MIN_SPEED;
}

bool PlayerRacket::canSpeedUp() const
{
	return data.getSpeed() < duels::RACKET_MAX_SPEED;
}

double PlayerRacket::getSpeed() const
{
	return data.getSpeed();
}

void PlayerRacket::updateFreezeState()
{
	data.unfreezeIfPossible();
}

bool PlayerRacket::canBeFreeze() const
{
	return data.canBeFreezed();
}

void PlayerRacket::freezeRacket()
{
	data.startFreeze( std::chrono::milliseconds{2000} );
}