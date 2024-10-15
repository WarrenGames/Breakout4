#ifndef GAME_CONTEXT_ONE_PLAYER_PLAYED_TIME_COUNTER_H
#define GAME_CONTEXT_ONE_PLAYER_PLAYED_TIME_COUNTER_H

#include "pausedTimesCounter/pausedTimesCounter.h"
#include "texturing/texturesCombo.h"
#include "text/sdl2ttf_font.h"

struct Essentials;

struct PlayedTimeCounter
{
	sdl2::Font arial;
	TextureCombo chronoText;
	AccurateTimeDelay elapsedTimeSinceLevelStart;
	AccurateTimeDelay textureRefreshDelay;
	PausedTimesCounter pausedTimeCounter;
	std::chrono::duration< long double, std::milli > atPlayingElapsedTime;
	bool isInPause;
	
	explicit PlayedTimeCounter(Essentials& essentials);
	~PlayedTimeCounter() = default;
	PlayedTimeCounter( const PlayedTimeCounter& ) = delete;
	PlayedTimeCounter& operator= ( const PlayedTimeCounter& ) = delete;
	PlayedTimeCounter( PlayedTimeCounter&& ) = default;
	PlayedTimeCounter& operator= ( PlayedTimeCounter&& ) = default;

	void pauseTheGame();
	void carryOnTheGame();
	void updateTextureIfNeeded(Essentials& essentials);
	void makeElapsedTimeText(Essentials& essentials);
	void setPlayedTime();
	void drawElapsedTimeTexture(Essentials& essentials) const;
};

#endif //GAME_CONTEXT_ONE_PLAYER_PLAYED_TIME_COUNTER_H