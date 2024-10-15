#ifndef INTERFACE_GENERATOR_LANGUAGE_TEXTURES_OPTIONS_H
#define INTERFACE_GENERATOR_LANGUAGE_TEXTURES_OPTIONS_H

#include "texturing/texturePosition.h"
#include "advancedDrawing/interfaceGeneratorLanguage/optionsStructs/colorComponent.h"
#include "fileSystem/fileSystem.h"
#include <string>

namespace igl{

namespace texture{
	
	struct ImageOptions
	{
		std::string texturePath;
		
		ImageOptions() = default;
		~ImageOptions() = default;
		ImageOptions( const ImageOptions& ) = default;
		ImageOptions& operator= ( const ImageOptions& ) = default;
	};
	
	struct TextOptions
	{
		unsigned textsBlocksIndex;
		igl::Color color;
		
		TextOptions();
		~TextOptions() = default;
		TextOptions( const TextOptions& ) = default;
		TextOptions& operator= ( const TextOptions& ) = default;
	};
	
	struct Description
	{
		fs::path scriptFilePath;
		std::string fileLine;
		std::string identifier;
		unsigned fileLineNumber;
		unsigned textureType;
		unsigned waitingType;
		igl::texture::ImageOptions imageOptions;
		igl::texture::TextOptions textOptions;
		TexturePosition position;
		int squareSize;
		bool isLoadingPerfect;
		
		explicit Description(const fs::path& toOpenFile, int squareSize_);
		~Description() = default;
		Description( const Description& ) = delete;
		Description& operator= ( const Description& ) = delete;
		Description( Description&& ) = default;
		Description& operator= ( Description&& ) = default;
	};
}

}

#endif //INTERFACE_GENERATOR_LANGUAGE_TEXTURES_OPTIONS_H