#include "demosLoadingAndSaving/moveStacks/moveDemosStacks.h"
#include "levelComponents/inputs/userInputs.h"
#include "levelComponents/global/globalGameObject.h"
#include "levelComponents/demosObjects/antarcticDemoPackage.h"
#include "levelComponents/demosObjects/demoMainPackage.h"

void demos::giveStacksContentsToMainPackage(LevelComponents& levelComponents, LevelInputs& levelInputs, demos::MainPackage& demosMainPackage)
{
	levelInputs.giveStacksContentsToMainPackage(demosMainPackage);
	levelComponents.giveStacksContentsToMainPackage(demosMainPackage);
}

void demos::giveStacksContentsToMainPackage(demos::DemoAntarcticPackage& demoAntarcticPackage, demos::MainPackage& demosMainPackage)
{
	demosMainPackage.antarcticDemoPackage.pinguinsPositions = std::move( demoAntarcticPackage.pinguinsPositions );
	demosMainPackage.antarcticDemoPackage.pinguinsDirection = std::move( demoAntarcticPackage.pinguinsDirection );
	demosMainPackage.antarcticDemoPackage.pinguinsCreateAndDestroy = std::move( demoAntarcticPackage.pinguinsCreateAndDestroy );
	demosMainPackage.antarcticDemoPackage.pinguinsQuacks = std::move( demoAntarcticPackage.pinguinsQuacks );
}

void demos::giveStacksToLevelComponents(LevelComponents& levelComponents, LevelInputs& levelInputs, demos::MainPackage& demosMainPackage)
{
	levelInputs.moveMainPackageToInputs(demosMainPackage);
	levelComponents.moveMainPackageToLevelComponents(demosMainPackage);
}

void demos::giveStacksToLevelComponents(demos::DemoAntarcticPackage& demoAntarcticPackage, demos::MainPackage& demosMainPackage)
{
	demoAntarcticPackage.pinguinsPositions = std::move( demosMainPackage.antarcticDemoPackage.pinguinsPositions );
	demoAntarcticPackage.pinguinsDirection = std::move( demosMainPackage.antarcticDemoPackage.pinguinsDirection );
	demoAntarcticPackage.pinguinsCreateAndDestroy = std::move( demosMainPackage.antarcticDemoPackage.pinguinsCreateAndDestroy );
	demoAntarcticPackage.pinguinsQuacks = std::move( demosMainPackage.antarcticDemoPackage.pinguinsQuacks );
}