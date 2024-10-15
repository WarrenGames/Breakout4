#ifndef GAME_DRAW_FREQUENCY_LOADING_MODULE_H
#define GAME_DRAW_FREQUENCY_LOADING_MODULE_H

#include "time/accurateTime.h"

struct AppLogFiles;
class PrefPathFinder;

class DrawFrequencyModule
{
private:
	std::chrono::microseconds refreshTime;
	unsigned framesPerSecond;
	AccurateTimeDelay drawDelay;
	bool isLoadingPerfect;

public:
	explicit DrawFrequencyModule(AppLogFiles& logs, const PrefPathFinder& prefPath);
	~DrawFrequencyModule() = default;
	DrawFrequencyModule( const DrawFrequencyModule& ) = delete;
	DrawFrequencyModule& operator= ( const DrawFrequencyModule& ) = delete;
	DrawFrequencyModule( DrawFrequencyModule&& ) = default;
	DrawFrequencyModule& operator= ( DrawFrequencyModule&& ) = default;
	
	operator bool() const;
	bool canDrawGame();
	unsigned getFramesPerSecond() const;
	void changeFramesPerSecond(unsigned newFramePerSecondValue);
	
private:
	void openDrawFrequencyFile(AppLogFiles& logs, const PrefPathFinder& prefPath);
};

#endif //GAME_DRAW_FREQUENCY_LOADING_MODULE_H