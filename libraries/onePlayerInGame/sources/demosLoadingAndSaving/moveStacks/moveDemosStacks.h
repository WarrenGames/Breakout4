#ifndef ONE_PLAYER_STD_DEMOS_MOVE_STACK_CONTEXT_H
#define ONE_PLAYER_STD_DEMOS_MOVE_STACK_CONTEXT_H

struct LevelComponents;
class LevelInputs;

namespace demos{
	struct MainPackage;
	struct DemoAntarcticPackage;
	
	//Needed to 'record' a demo (not to 'run' a demo) after a demo is complete
	void giveStacksContentsToMainPackage(LevelComponents& levelComponents, LevelInputs& levelInputs, demos::MainPackage& demosMainPackage);
	void giveStacksContentsToMainPackage(demos::DemoAntarcticPackage& antarcticPackage, demos::MainPackage& demosMainPackage);
	void setStartingBricksMatrixForSavingLatter(const LevelComponents& levelComponents, demos::MainPackage& demosMainPackage);
	
	
	//Needed to run a 'pre-recorded' demo (not to 'record' a demo)
	void giveStacksToLevelComponents(LevelComponents& levelComponents, LevelInputs& levelInputs, demos::MainPackage& demosMainPackage);
	void giveStacksToLevelComponents(demos::DemoAntarcticPackage& antarcticPackage, demos::MainPackage& demosMainPackage);
}

#endif //ONE_PLAYER_STD_DEMOS_MOVE_STACK_CONTEXT_H