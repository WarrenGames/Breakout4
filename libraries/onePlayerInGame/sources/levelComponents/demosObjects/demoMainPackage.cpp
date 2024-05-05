#include "levelComponents/demosObjects/demoMainPackage.h"
#include "demos/loading/loadDemosVectorsDataSize.h"
#include "prefPath/prefPathFinder.h"
#include "demosLoadingAndSaving/loading/stackSquareSizeLegacy.h"
#include "generic/fileSystem/fileProcessing/filesNames.h"
#include "demos/consts/demosConsts.h"
#include "consts/onePlayerGridConsts.h"
#include "consts/constexprScreen.h"

demos::MainPackage::MainPackage(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned gameKind):
	inputData{ logs, demos::getVectorsDataSize(logs, prefPath, file::DemoInputDataFile), gameKind, demos::InputDataStr },
	quitLevelEvent{ logs, demos::getVectorsDataSize(logs, prefPath, file::DemoQuitEventFile), gameKind, demos::QuitLevelEventStr },
	traceCrossPosition{ logs, demos::getVectorsDataSize(logs, prefPath, file::DemoTraceCrossPositionFile), gameKind, demos::TraceCrossPositionStr },
	racketPosition{ logs, demos::getVectorsDataSize(logs, prefPath, file::DemoRacketPositionFile), gameKind, demos::RacketPositionStr },
	ballPosition{ logs, demos::getVectorsDataSize(logs, prefPath, file::DemoBallPositionFile), gameKind, demos::BallPositionStr },
	brickDestruction{ logs, demos::getVectorsDataSize(logs, prefPath, file::DemoBrickDestructionFile), gameKind, demos::BrickDestructionStr },
	soundsStack{ logs, demos::getVectorsDataSize(logs, prefPath, file::DemoSoundsEventsFile), gameKind, demos::SoundEventStr },
	antarcticDemoPackage{ logs, prefPath, gameKind },
	demoKind{gameKind}
{
	
}

bool demos::MainPackage::wasLoadingPerfect() const
{
	return inputData && quitLevelEvent && traceCrossPosition && racketPosition && ballPosition && brickDestruction && soundsStack;
}

void demos::MainPackage::useLegacyTransformsIfAny()
{
	if( startingData.squareSizeAtSaving != SQR_SIZE )
	{
		transformPositionStackWithLegacy(traceCrossPosition, startingData.squareSizeAtSaving);
		transformPositionStackWithLegacy(racketPosition, startingData.squareSizeAtSaving);
		transformPositionStackWithLegacy(ballPosition, startingData.squareSizeAtSaving);
		antarcticDemoPackage.useLegacyTransformsIfAny(startingData.squareSizeAtSaving);
	}
}
