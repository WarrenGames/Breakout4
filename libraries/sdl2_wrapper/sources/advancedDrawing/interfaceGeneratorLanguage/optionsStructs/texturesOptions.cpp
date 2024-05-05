#include "advancedDrawing/interfaceGeneratorLanguage/optionsStructs/texturesOptions.h"
#include "advancedDrawing/interfaceGeneratorLanguage/interfaceGeneratorConsts.h"

igl::texture::TextOptions::TextOptions():
	textsBlocksIndex{0},
	color{}
{
	
}

igl::texture::Description::Description(const fs::path& toOpenFile, unsigned squareSize_):
	scriptFilePath{toOpenFile},
	fileLineNumber{1},
	textureType{igl::texture::TextureIsMax},
	waitingType{ igl::texture::AwaitTextureId },
	imageOptions{},
	textOptions{},
	squareSize{squareSize_},
	isLoadingPerfect{true}
{
	
}