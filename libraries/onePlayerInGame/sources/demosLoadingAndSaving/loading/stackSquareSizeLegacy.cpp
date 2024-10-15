#include "demosLoadingAndSaving/loading/stackSquareSizeLegacy.h"
#include "demos/templates/demoStack.h"
#include "demos/positions/taggedPositionStackData.h"
#include "demos/positions/positionStackData.h"
#include "consts/constexprScreen.h"

void transformPositionStackWithLegacy(demos::Stack< demos::PositionStackData >& stack, int squareSizeAtSaving)
{
	if( stack.getCommandsNumber() > 0 )
	{
		for( auto &data : stack )
		{
			data.position.x = data.position.x * SQR_SIZE / squareSizeAtSaving;
			data.position.y = data.position.y * SQR_SIZE / squareSizeAtSaving;
		}
	}
}

void transformPositionStackWithLegacy(demos::Stack< demos::TaggedPositionStackData >& stack, int squareSizeAtSaving)
{
	if( stack.getCommandsNumber() > 0 )
	{
		for( auto &data : stack )
		{
			data.position.x = data.position.x * SQR_SIZE / squareSizeAtSaving;
			data.position.y = data.position.y * SQR_SIZE / squareSizeAtSaving;
		}
	}
}