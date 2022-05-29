#ifndef INTERFACE_GENERATOR_LANGUAGE_TEXTURES_OPTIONS_H
#define INTERFACE_GENERATOR_LANGUAGE_TEXTURES_OPTIONS_H

#include "texturing/texturePosition.h"
#include "advancedDrawing/interfaceGeneratorLanguage/optionsStructs/colorComponent.h"
#include <string>

namespace igl{

namespace texture{
	
	struct ImageOptions
	{
		std::string texturePath;
		
		ImageOptions() = default;
	};
	
	struct TextOptions
	{
		unsigned textsBlocksIndex;
		igl::Color color;
		
		TextOptions();
	};
	
	struct Description
	{
		std::string scriptFilePath;
		std::string fileLine;
		std::string identifier;
		unsigned fileLineNumber;
		unsigned textureType;
		unsigned waitingType;
		igl::texture::ImageOptions imageOptions;
		igl::texture::TextOptions textOptions;
		TexturePosition position;
		unsigned squareSize;
		bool isLoadingPerfect;
		
		explicit Description(const std::string& toOpenFile, unsigned squareSize_);
	};
}

}

#endif //INTERFACE_GENERATOR_LANGUAGE_TEXTURES_OPTIONS_H