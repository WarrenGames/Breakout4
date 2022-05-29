#ifndef CHAMIONSHIP_END_CONTEXT_H
#define CHAMIONSHIP_END_CONTEXT_H

struct Essentials;
class DuelsEndInterface;

namespace duels{
	struct LevelOptions;
	
	namespace end{
		void context(Essentials& essentials, unsigned finalScore, const duels::LevelOptions& levelOptions);
		
		bool isThereAWinningScore(unsigned finalScore, const duels::LevelOptions& levelOptions);
		
		void mainLoop(Essentials& essentials, const duels::LevelOptions& levelOptions);
		
		void quitChampionshipEnd(Essentials& essentials, bool& quitSum);
		
		void drawInterface(Essentials& essentials, const DuelsEndInterface& interface, const LevelOptions& levelOptions);
	}
}

#endif //CHAMIONSHIP_END_CONTEXT_H