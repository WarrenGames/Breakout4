#ifndef ONE_P_IN_GAME_LVL_COMPONENTS_DEMOS_MAIN_PACKAGE_H
#define ONE_P_IN_GAME_LVL_COMPONENTS_DEMOS_MAIN_PACKAGE_H

#include "levelComponents/demosObjects/playerStartingData.h"
#include "demos/inputs/actionData.h"
#include "demos/objectsDestruction/matrixDemoData.h"
#include "demos/positions/positionStackData.h"
#include "demos/sounds/soundsStackData.h"
#include "demos/templates/demoStack.h"
#include "levelComponents/demosObjects/antarcticDemoPackage.h"

struct AppLogFiles;
class PrefPathFinder;

namespace demos{

struct MainPackage
{
	demos::StartingData startingData;
	demos::Stack< demos::ActionData > inputData;
	demos::Stack< demos::ActionData > quitLevelEvent;
	demos::Stack< demos::PositionStackData > traceCrossPosition;
	demos::Stack< demos::PositionStackData > racketPosition;
	demos::Stack< demos::PositionStackData > ballPosition;
	demos::Stack< demos::Matrix2DAction > brickDestruction;
	demos::Stack< demos::SoundStackData > soundsStack;
	demos::DemoAntarcticPackage antarcticDemoPackage;
	unsigned demoKind;
	
	explicit MainPackage(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned gameKind);
	~MainPackage() = default;
	MainPackage( const MainPackage& ) = delete;
	MainPackage& operator= ( const MainPackage& ) = delete;
	MainPackage( MainPackage&& ) = default;
	MainPackage& operator= ( MainPackage&& ) = default;
	
	bool wasLoadingPerfect() const;
	
	void useLegacyTransformsIfAny();
	
};

}

#endif //ONE_P_IN_GAME_LVL_COMPONENTS_DEMOS_MAIN_PACKAGE_H