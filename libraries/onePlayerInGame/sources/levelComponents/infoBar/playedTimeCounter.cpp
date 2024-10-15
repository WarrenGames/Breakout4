#include "levelComponents/infoBar/playedTimeCounter.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "consts/constexprScreen.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"
#include <string>

PlayedTimeCounter::PlayedTimeCounter(Essentials& essentials):
	arial{essentials.logs.error, ArialFontPath, FontBigPointSize },
	atPlayingElapsedTime{ std::chrono::milliseconds{0} },
	isInPause{true}
{
	makeElapsedTimeText(essentials);
	pauseTheGame();
}

void PlayedTimeCounter::pauseTheGame()
{
	if( false == isInPause )
	{
		isInPause = true;
		pausedTimeCounter.setPrecedent();
	}
}

void PlayedTimeCounter::carryOnTheGame()
{
	if( isInPause )
	{
		isInPause = false;
		pausedTimeCounter.endPauseAndStackDuration();
		setPlayedTime();
	}
}

void PlayedTimeCounter::updateTextureIfNeeded(Essentials& essentials)
{
	if( false == isInPause && textureRefreshDelay.hasTimeElapsed(std::chrono::milliseconds{1000} ) )
	{
		setPlayedTime();
		textureRefreshDelay.joinTimePoints();
		makeElapsedTimeText(essentials);
	}
}

void PlayedTimeCounter::makeElapsedTimeText(Essentials& essentials)
{
	if( arial )
	{
		chronoText.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, std::to_string(static_cast<int>( atPlayingElapsedTime.count() / 1000) ), YellowColor);
		chronoText.resetSpritePosition( TexturePosition{ GameScreenWidth / 2, SQR_SIZE / 2, true, true } );
	}
}

void PlayedTimeCounter::setPlayedTime()
{
	atPlayingElapsedTime = elapsedTimeSinceLevelStart.getCurrentElapsedMillisecondsTime() - pausedTimeCounter.getStackedTime();
}

void PlayedTimeCounter::drawElapsedTimeTexture(Essentials& essentials) const
{
	if( chronoText )
	{
		chronoText.draw(essentials.rndWnd);
	}
}