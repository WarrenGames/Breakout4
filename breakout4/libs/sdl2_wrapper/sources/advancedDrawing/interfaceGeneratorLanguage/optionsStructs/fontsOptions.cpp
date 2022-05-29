#include "advancedDrawing/interfaceGeneratorLanguage/optionsStructs/fontsOptions.h"

igl::font::Description::Description(const std::string& toOpenFile, unsigned squareSize_):
	scriptFilePath{ toOpenFile },
	fontSize{ 0 },
	fileLineNumber{1},
	squareSize{ squareSize_ },
	isLoadingPerfect{true}
{
	
}