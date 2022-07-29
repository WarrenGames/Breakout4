#include "contexts/gameCommon/pinguins/pinguinDrawData.h"
#include "generic/maths/orientation.h"
#include "contexts/gameCommon/pinguins/pinguinConsts.h"
#include "consts/constexprScreen.h"
#include "SDL_rect.h"

PinguinDrawData::PinguinDrawData(const AccurCoords& pinguinPos, double speed, const Offset& dirVectors):
	direction{0},
	frameNumber{0},
	move{pinguinPos, speed, dirVectors}
{
	
}

void PinguinDrawData::animPinguin()
{
	if( anim.hasTimeElapsed( std::chrono::milliseconds{pinguin::ANIM_DELAY} ) )
	{
		if( frameNumber + 1 < pinguin::ANIM_FRAMES_NUMBER )
		{
			++frameNumber;
		}
		else{
			frameNumber = 0;
		}
		anim.joinTimePoints();
	}
}

void PinguinDrawData::bounceOffScreenEdges(int topycoord, const SDL_Rect& collisionRect)
{
	bounceOffScreenTop(topycoord, collisionRect);
	bounceOffScreenBottom(collisionRect);
	bounceOffScreenLeft(collisionRect);
	bounceOffScreenRight(collisionRect);
}

void PinguinDrawData::bounceOffScreenRight(const SDL_Rect& collisionRect)
{
	if( move.get_x_position() + collisionRect.w / 2 >= GAME_SCREEN_WIDTH && move.get_x_norm() > 0 )
	{
		move.reverse_x_vector();
		move.adjust_x_speed();
		setDirection();
	}
}

void PinguinDrawData::bounceOffScreenLeft(const SDL_Rect& collisionRect)
{
	if( move.get_x_position() - collisionRect.w / 2 <= 0 && move.get_x_norm() < 0 )
	{
		move.reverse_x_vector();
		move.adjust_x_speed();
		setDirection();
	}
}

void PinguinDrawData::bounceOffScreenTop(int topycoord, const SDL_Rect& collisionRect)
{
	if( move.get_y_position() - collisionRect.h / 2 <= topycoord && move.get_y_norm() < 0 )
	{
		move.reverse_y_vector();
		move.adjust_y_speed();
		setDirection();
	}
}

void PinguinDrawData::bounceOffScreenBottom(const SDL_Rect& collisionRect)
{
	if( move.get_y_position() + collisionRect.h / 2 >= GAME_SCREEN_HEIGHT && move.get_y_norm() > 0 )
	{
		move.reverse_y_vector();
		move.adjust_y_speed();
		setDirection();
	}
}

void PinguinDrawData::setDirection()
{
	direction = static_cast<int>( getDirection( pinguin::TEXTURE_DIRECTIONS_NUMBER, move.get_x_norm(), move.get_y_norm() ) );
	if( direction >= pinguin::TEXTURE_DIRECTIONS_NUMBER )
	{
		direction = 0;
	}
}