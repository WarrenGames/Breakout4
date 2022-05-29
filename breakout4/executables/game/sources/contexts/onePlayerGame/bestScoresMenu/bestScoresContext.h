#ifndef ONE_PLAYER_BEST_SCORES_CONTEXT_H
#define ONE_PLAYER_BEST_SCORES_CONTEXT_H

struct Essentials;
class ScoresInterface;

namespace bestScores{
	void context(Essentials& essentials);
	
	void fromGameEndContext(Essentials& essentials, unsigned playerScore, unsigned skill, unsigned raceType);
	
	void mainLoop(Essentials& essentials, ScoresInterface& interface, bool& quitMenu);
	
	void update(Essentials& essentials, ScoresInterface& interface, bool& quitMenu);
	
	void quitWithEscapeOrWindowsClosing(Essentials& essentials, bool& quitMenu);
	
	void quitWithButton(const ScoresInterface& interface, bool& quitMenu);
	
	void drawEverything(Essentials& essentials, ScoresInterface& interface, bool& quitMenu);
}

#endif //ONE_PLAYER_BEST_SCORES_CONTEXT_H