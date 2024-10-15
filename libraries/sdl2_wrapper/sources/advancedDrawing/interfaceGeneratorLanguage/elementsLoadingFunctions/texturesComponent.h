#ifndef INTERFACE_GENERATOR_LANGUAGE_TEXTUE_COMPONENT_H
#define INTERFACE_GENERATOR_LANGUAGE_TEXTUE_COMPONENT_H

// To use theses functionalities run 'either' openScriptFileWithImageOnly() or openScriptFile()

#include "texturing/texturesCombo.h"
#include "fileSystem/fileSystem.h"
#include <vector>
#include <string>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; class Font; }
class TextsBlocks;

namespace igl{

namespace texture{
	struct Description;
	
	void openScriptFileWithImageOnly(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, std::vector< TextureCombo >& textures, const fs::path& scriptFile, int squareSize);
	
	void openScriptFile(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const TextsBlocks& texts, 
						std::vector< TextureCombo >& textures, const fs::path& scriptFile, int squareSize);
	
	void checkData(const TextsBlocks& texts, const igl::texture::Description& data);
	
	void checkTextureType(const igl::texture::Description& data);
	
	void checkTextsBlocks(const TextsBlocks& texts, const igl::texture::Description& data);
	
	void addTextureIfNothingFailed(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const TextsBlocks& texts, 
										std::vector< TextureCombo >& textures, const igl::texture::Description& data);
	
	void addImageTexture(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, std::vector< TextureCombo >& textures, const igl::texture::Description& data);
	
	void addTextTexture(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const TextsBlocks& texts, 
							std::vector< TextureCombo >& textures, const igl::texture::Description& data);
							
	void readIdentifierStarting(igl::texture::Description& data, std::istringstream& lineStream);
	
	void processTextureId(igl::texture::Description& data, std::istringstream& lineStream);
	
	void processTextureType(igl::texture::Description& data, std::istringstream& lineStream);
	
	void processImageTexture(igl::texture::Description& data, std::istringstream& lineStream);
	
	void processTextsBlocksIndex(igl::texture::Description& data, std::istringstream& lineStream);
	
	void processTextColor(igl::texture::Description& data, std::istringstream& lineStream);
	
	void processPositionCoordinates(igl::texture::Description& data, std::istringstream& lineStream);
	
	void processCoordinates(igl::texture::Description& data, std::istringstream& lineStream);
	
	void processCenteredPositions(igl::texture::Description& data, std::istringstream& lineStream);
	
	void processXCenterPosition(igl::texture::Description& data, std::istringstream& lineStream, TexturePosition& position);
	
	void processYCenterPosition(igl::texture::Description& data, std::istringstream& lineStream, TexturePosition& position);
	
	std::string getErrorMessage(const std::string& waitingToken, const std::string& expectedThing);
}

}

#endif //INTERFACE_GENERATOR_LANGUAGE_TEXTUE_COMPONENT_H