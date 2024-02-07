#include "contexts/onePlayerGame/bestScoresMenu/bestScoresContext.h"
#include "contexts/onePlayerGame/bestScoresMenu/mainInterface.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"

void bestScores::context(Essentials& essentials)
{
	ScoresInterface interface{essentials};
	bool quitMenu{false};
	bestScores::mainLoop(essentials, interface, quitMenu);
}

void bestScores::fromGameEndContext(Essentials& essentials, unsigned playerScore, unsigned skill, unsigned raceType)
{
	ScoresInterface interface{essentials, playerScore, skill, raceType};
	bool quitMenu{false};
	bestScores::mainLoop(essentials, interface, quitMenu);
	interface.saveScoresToFile(essentials, raceType);
}

void bestScores::mainLoop(Essentials& essentials, ScoresInterface& interface, bool& quitMenu)
{
	while( false == quitMenu )
	{
		essentials.inp.updateEvents();
		bestScores::update(essentials, interface, quitMenu);
		bestScores::drawEverything(essentials, interface, quitMenu);
	}
}

void bestScores::update(Essentials& essentials, ScoresInterface& interface, bool& quitMenu)
{
	interface.update(essentials);
	bestScores::quitWithEscapeOrWindowsClosing(essentials, quitMenu);
	bestScores::quitWithButton(interface, quitMenu);
}

void bestScores::quitWithEscapeOrWindowsClosing(Essentials& essentials, bool& quitMenu)
{
	if( essentials.inp.getKeyState(input::KeybOut) || essentials.inp.getSDL_quit() )
	{
		quitMenu = true;
		essentials.inp.setKeyStateToFalse(input::KeybOut);
	}
}

void bestScores::quitWithButton(const ScoresInterface& interface, bool& quitMenu)
{
	if( interface.quitMenu() )
	{
		quitMenu = true;
	}
}

void bestScores::drawEverything(Essentials& essentials, ScoresInterface& interface, bool& quitMenu)
{
	if( false == quitMenu )
	{
		interface.drawEverything(essentials);
		essentials.rndWnd.displayRenderer();
		SDL_Delay(SdlDelayTime);
	}
}