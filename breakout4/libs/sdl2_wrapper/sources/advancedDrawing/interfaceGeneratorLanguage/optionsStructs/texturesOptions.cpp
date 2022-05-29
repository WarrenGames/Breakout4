#include "advancedDrawing/interfaceGeneratorLanguage/optionsStructs/texturesOptions.h"
#include "advancedDrawing/interfaceGeneratorLanguage/interfaceGeneratorConsts.h"

igl::texture::TextOptions::TextOptions():
	textsBlocksIndex{0},
	color{}
{
	
}

igl::texture::Description::Description(const std::string& toOpenFile, unsigned squareSize_):
	scriptFilePath{toOpenFile},
	fileLineNumber{1},
	textureType{igl::texture::TEXTURE_IS_MAX},
	waitingType{ igl::texture::AWAIT_TEXTURE_ID },
	imageOptions{},
	textOptions{},
	squareSize{squareSize_},
	isLoadingPerfect{true}
{
	
}