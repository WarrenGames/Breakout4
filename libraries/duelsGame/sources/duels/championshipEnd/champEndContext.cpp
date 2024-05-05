#include "duels/championshipEnd/champEndContext.h"
#include "types/essentialsStruct.h"
#include "duels/inGameObjects/gameElements/duelsLevelOptions.h"
#include "duels/championshipEnd/matchEndInterface.h"
#include "consts/sdlColors.h"
#include <algorithm>

void duels::end::context(Essentials& essentials, unsigned finalScore, const duels::LevelOptions& levelOptions)
{
	if( duels::end::isThereAWinningScore(finalScore, levelOptions) )
	{
		duels::end::mainLoop(essentials, levelOptions);
	}
}

bool duels::end::isThereAWinningScore(unsigned finalScore, const duels::LevelOptions& levelOptions)
{
	return std::any_of(levelOptions.playersScores.cbegin(), levelOptions.playersScores.cend(), [finalScore](int score){return score >= static_cast<int>(finalScore);} );
}

void duels::end::mainLoop(Essentials& essentials, const duels::LevelOptions& levelOptions)
{
	bool quitSum{false};
	DuelsEndInterface interface{essentials, levelOptions};
	while( false == quitSum )
	{
		essentials.inp.updateEvents();
		duels::end::quitChampionshipEnd(essentials, quitSum);
		duels::end::drawInterface(essentials, interface, levelOptions);
	}
}

void duels::end::quitChampionshipEnd(Essentials& essentials, bool& quitSum)
{
	if( essentials.inp.getKeyState(input::KeybOut) || essentials.inp.getSDL_quit() )
	{
		quitSum = true;
	}
}

void duels::end::drawInterface(Essentials& essentials, const DuelsEndInterface& interface, const LevelOptions& levelOptions)
{
	essentials.rndWnd.clearScreen(BlackColor);
	interface.drawEverything(essentials, levelOptions);
	essentials.rndWnd.displayRenderer();
	SDL_Delay(SdlDelayTime);
}