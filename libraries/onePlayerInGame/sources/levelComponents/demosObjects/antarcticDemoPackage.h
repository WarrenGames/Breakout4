#ifndef ONE_P_IN_GAME_LVL_COMPONENTS_DEMOS_ANTARCTIC_PACKAGE_H
#define ONE_P_IN_GAME_LVL_COMPONENTS_DEMOS_ANTARCTIC_PACKAGE_H

#include "demos/positions/taggedPositionStackData.h"
#include "demos/objectDirections/objectDirectionData.h"
#include "demos/inputs/actionData.h"
#include "demos/sounds/soundsStackData.h"
#include "demos/templates/demoStack.h"

struct AppLogFiles;
class PrefPathFinder;

namespace demos{

struct DemoAntarcticPackage
{
	demos::Stack< demos::TaggedPositionStackData > pinguinsPositions;
	demos::Stack< demos::TaggedDirectionStackData > pinguinsDirection;
	demos::Stack< demos::ActionData > pinguinsCreateAndDestroy;
	demos::Stack< demos::SoundStackData > pinguinsQuacks;
	unsigned demoKind;
	
	explicit DemoAntarcticPackage(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned gameKind);
	~DemoAntarcticPackage() = default;
	DemoAntarcticPackage( const DemoAntarcticPackage& ) = delete;
	DemoAntarcticPackage& operator= ( const DemoAntarcticPackage& ) = delete;
	DemoAntarcticPackage( DemoAntarcticPackage&& ) = default;
	DemoAntarcticPackage& operator= ( DemoAntarcticPackage&& ) = default;
	
	bool wasLoadingPerfect() const;
	
	void useLegacyTransformsIfAny(int squareSizeAtSaving);
	
	void joinDemosTimePoints();
};

}

#endif //ONE_P_IN_GAME_LVL_COMPONENTS_DEMOS_ANTARCTIC_PACKAGE_H