#include "levelComponents/demosObjects/antarcticDemoPackage.h"
#include "demos/loading/loadDemosVectorsDataSize.h"
#include "prefPath/prefPathFinder.h"
#include "demosLoadingAndSaving/loading/stackSquareSizeLegacy.h"
#include "generic/fileSystem/fileProcessing/filesNames.h"
#include "demos/consts/demosConsts.h"
#include "consts/onePlayerGridConsts.h"
#include "consts/constexprScreen.h"

demos::DemoAntarcticPackage::DemoAntarcticPackage(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned gameKind):
	pinguinsPositions{ logs, demos::getVectorsDataSize(logs, prefPath, file::DemoPinguinsFile), gameKind, demos::PinguinsPositionDataStr },
	pinguinsDirection{ logs, demos::getVectorsDataSize(logs, prefPath, file::DemoPinguinsFile), gameKind, demos::PinguinsDirectionDataStr },
	pinguinsCreateAndDestroy{ logs, demos::getVectorsDataSize(logs, prefPath, file::DemoPinguinsFile), gameKind, demos::PinguinsCreateAndDestroyStr },
	pinguinsQuacks{ logs, demos::getVectorsDataSize(logs, prefPath, file::DemoPinguinsFile), gameKind, demos::PinguinsQuackSound },
	demoKind{ gameKind }
{
	
}

bool demos::DemoAntarcticPackage::wasLoadingPerfect() const
{
	return pinguinsPositions && pinguinsDirection && pinguinsCreateAndDestroy && pinguinsQuacks;
}

void demos::DemoAntarcticPackage::useLegacyTransformsIfAny(int squareSizeAtSaving)
{
	if( squareSizeAtSaving != SQR_SIZE )
	{
		transformPositionStackWithLegacy(pinguinsPositions, squareSizeAtSaving);
	}
}

void demos::DemoAntarcticPackage::joinDemosTimePoints()
{
	pinguinsPositions.setPrecedentTimePoint();
	pinguinsDirection.setPrecedentTimePoint();
	pinguinsCreateAndDestroy.setPrecedentTimePoint();
	pinguinsQuacks.setPrecedentTimePoint();
}