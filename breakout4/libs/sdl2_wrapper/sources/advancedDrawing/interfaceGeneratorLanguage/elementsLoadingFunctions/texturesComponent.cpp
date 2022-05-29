#include "advancedDrawing/interfaceGeneratorLanguage/elementsLoadingFunctions/texturesComponent.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "text/sdl2ttf_font.h"
#include "texts/textLoader.h"
#include "wrappers/rectStream.h"
#include "advancedDrawing/interfaceGeneratorLanguage/optionsStructs/texturesOptions.h"
#include "advancedDrawing/interfaceGeneratorLanguage/interfaceGeneratorConsts.h"
#include <stdexcept>
#include <sstream>

void igl::texture::openScriptFileWithImageOnly(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, std::vector< TextureCombo >& textures, const std::string& scriptFile, unsigned squareSize)
{
	if( std::ifstream textureDescriptionFile{ scriptFile } )
	{
		try
		{
			std::string fileLine;
			while( std::getline( textureDescriptionFile, fileLine ) )
			{
				std::istringstream lineStream{fileLine};
				igl::texture::Description data{scriptFile, squareSize};
				igl::texture::readIdentifierStarting(data, lineStream);
				igl::texture::addImageTexture(logs, rndWnd, textures, data);
				data.fileLineNumber++;
			}
		}
		catch( const std::runtime_error& e )
		{
			logs.error << e.what() << "\n";
		}
	}
	else{
		logs.error.wrFileOpeningError(scriptFile, "load 'TextureCombo' description");
	}
}

void igl::texture::openScriptFile(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const TextsBlocks& texts, 
									std::vector< TextureCombo >& textures, const std::string& scriptFile, unsigned squareSize)
{
	if( std::ifstream textureDescriptionFile{ scriptFile } )
	{
		try
		{
			std::string fileLine;
			while( std::getline( textureDescriptionFile, fileLine ) )
			{
				std::istringstream lineStream{fileLine};
				igl::texture::Description data{scriptFile, squareSize};
				igl::texture::readIdentifierStarting(data, lineStream);
				igl::texture::checkData(texts, data);
				igl::texture::addTextureIfNothingFailed(logs, rndWnd, font, texts, textures, data);
				data.fileLineNumber++;
			}
		}
		catch( const std::runtime_error& e )
		{
			logs.error << e.what() << "\n";
		}
	}
	else{
		logs.error.wrFileOpeningError(scriptFile, "load 'TextureCombo' description");
	}
}

void igl::texture::checkData(const TextsBlocks& texts, const igl::texture::Description& data)
{
	igl::texture::checkTextureType(data);
	if( igl::texture::TEXTURE_IS_TEXT == data.textureType )
	{
		igl::texture::checkTextsBlocks(texts, data);
	}
}

void igl::texture::checkTextureType(const igl::texture::Description& data)
{
	if( !( data.textureType < igl::texture::TEXTURE_IS_MAX ) )
	{
		throw std::runtime_error{"Error: bad 'texture type' number: " + std::to_string(data.textureType) + " in '" + data.scriptFilePath + "' file at line " 
								+ std::to_string(data.fileLineNumber) + " ."};
	}
}

void igl::texture::checkTextsBlocks(const TextsBlocks& texts, const igl::texture::Description& data)
{
	if( !( data.textOptions.textsBlocksIndex < texts.size() ) )
	{
		throw std::runtime_error{"Error: bad 'textsBlocks' index: " + std::to_string(data.textOptions.textsBlocksIndex) + " in '" + data.scriptFilePath + "' file at line " 
									+ std::to_string(data.fileLineNumber) + " ."};
	}
}

void igl::texture::addTextureIfNothingFailed(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const TextsBlocks& texts, 
												std::vector< TextureCombo >& textures, const igl::texture::Description& data)
{
	if( data.isLoadingPerfect )
	{
		switch( data.textureType )
		{
			case igl::texture::TEXTURE_IS_IMAGE:
				igl::texture::addImageTexture(logs, rndWnd, textures, data);
				break;
			case igl::texture::TEXTURE_IS_TEXT:
				igl::texture::addTextTexture(logs, rndWnd, font, texts, textures, data);
				break;
		}
	}
}

void igl::texture::addImageTexture(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, std::vector< TextureCombo >& textures, const igl::texture::Description& data)
{
	logs.warning << "Add 'image texture' '" << data.imageOptions.texturePath << "' with position: " << data.position << " \n";
	textures.emplace_back( TextureCombo{logs, rndWnd, data.imageOptions.texturePath, data.position} );
}

void igl::texture::addTextTexture(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fonts, const TextsBlocks& texts, 
									std::vector< TextureCombo >& textures, const igl::texture::Description& data)
{
	logs.warning << "Add 'text texture' '" << texts[data.textOptions.textsBlocksIndex] << "' with position: " << data.position << "\n";
	textures.emplace_back(TextureCombo{logs, rndWnd, fonts, texts[data.textOptions.textsBlocksIndex], data.textOptions.color.getSDLColor(), data.position} );
}

void igl::texture::readIdentifierStarting(igl::texture::Description& data, std::istringstream& lineStream)
{
	if( lineStream >> data.identifier )
	{
		igl::texture::processTextureId(data, lineStream);
	}
}

void igl::texture::processTextureId(igl::texture::Description& data, std::istringstream& lineStream)
{
	if( igl::texture::AWAIT_TEXTURE_ID == data.waitingType )
	{
		if( igl::texture::TEXTURE_ID == data.identifier )
		{
			if( lineStream >> data.identifier )
			{
				data.waitingType = igl::texture::AWAIT_TEXTURE_TYPE;
				igl::texture::processTextureType(data, lineStream);
			}
			else{
				throw std::runtime_error{ igl::texture::getErrorMessage(igl::texture::TEXTURE_ID, "reading 'Text' or 'Image' token")};
			}
		}
		else{
			throw std::runtime_error{ igl::texture::getErrorMessage(igl::texture::TEXTURE_ID, "line starting") };
		}
	}
}

void igl::texture::processTextureType(igl::texture::Description& data, std::istringstream& lineStream)
{
	if( igl::texture::AWAIT_TEXTURE_TYPE == data.waitingType )
	{
		if( igl::texture::IMAGE_ID == data.identifier )
		{
			data.textureType = igl::texture::TEXTURE_IS_IMAGE;
			data.waitingType = igl::texture::AWAIT_IMAGE_PATH;
			igl::texture::processImageTexture(data, lineStream);
		}
		else if( igl::texture::TEXT_ID == data.identifier )
		{
			data.textureType = igl::texture::TEXTURE_IS_TEXT;
			data.waitingType = igl::texture::AWAIT_TXT_BLOCKS_INDEX;
			igl::texture::processTextsBlocksIndex(data, lineStream);
		}
		else{
			throw std::runtime_error{ igl::texture::getErrorMessage(igl::texture::TEXTURE_ID, "reading 'Text' or 'Image' token") };
		}
	}
}

void igl::texture::processImageTexture(igl::texture::Description& data, std::istringstream& lineStream)
{
	if( igl::texture::AWAIT_IMAGE_PATH == data.waitingType )
	{
		if( lineStream >> data.imageOptions.texturePath )
		{
			data.waitingType = igl::texture::AWAIT_POSITION_COORD;
			igl::texture::processPositionCoordinates(data, lineStream);
		}
		else{
			throw std::runtime_error{igl::texture::getErrorMessage(igl::texture::IMAGE_ID, "image texture path") };
		}
	}
}

void igl::texture::processTextsBlocksIndex(igl::texture::Description& data, std::istringstream& lineStream)
{
	if( igl::texture::AWAIT_TXT_BLOCKS_INDEX == data.waitingType )
	{
		if( lineStream >> data.identifier >> data.textOptions.textsBlocksIndex )
		{
			if( igl::texture::TEXT_NUM == data.identifier )
			{
				data.waitingType = igl::texture::AWAIT_COLOR_COMPONENTS;
				igl::texture::processTextColor(data, lineStream);
			}
			else{
				throw std::runtime_error{ igl::texture::getErrorMessage(igl::texture::TEXT_NUM, "wrong identifier: " + data.identifier) };
			}
		}
		else{
			throw std::runtime_error{ igl::texture::getErrorMessage(igl::texture::TEXT_NUM, "textsBlocks vcetor index and TextsBlocks index") };
		}
	}
}

void igl::texture::processTextColor(igl::texture::Description& data, std::istringstream& lineStream)
{
	if( igl::texture::AWAIT_COLOR_COMPONENTS == data.waitingType )
	{
		if( lineStream >> data.identifier >> data.textOptions.color.red >> data.textOptions.color.green >> data.textOptions.color.blue >> data.textOptions.color.alpha )
		{
			data.waitingType = igl::texture::AWAIT_POSITION_COORD;
			igl::texture::processPositionCoordinates(data, lineStream);
		}
		else{
			throw std::runtime_error{ igl::texture::getErrorMessage(igl::texture::COLOR_ID, "red, green, blue, and alpha components reading failed") };
		}
	}
}

void igl::texture::processPositionCoordinates(igl::texture::Description& data, std::istringstream& lineStream)
{
	if( igl::texture::AWAIT_POSITION_COORD == data.waitingType )
	{
		if( lineStream >> data.identifier )
		{
			igl::texture::processCoordinates(data, lineStream);
		}
		else{
			data.position.position.x = 0;
			data.position.position.y = 0;
			data.position.on_x_centered = false;
			data.position.on_y_centered = false;
		}
	}
}

void igl::texture::processCoordinates(igl::texture::Description& data, std::istringstream& lineStream)
{
	if( igl::texture::PROP_POSITION_ID == data.identifier )
	{
		if( lineStream >> data.position.position.x >> data.position.position.y )
		{
			data.position.position.x = data.position.position.x * data.squareSize / 64;
			data.position.position.y = data.position.position.y * data.squareSize / 64;
			data.waitingType = igl::texture::AWAIT_CENTERED_POS;
			igl::texture::processCenteredPositions(data, lineStream);
		}
	}
	else if( igl::texture::STATIC_POSITION_ID == data.identifier )
	{
		if( lineStream >> data.position.position.x >> data.position.position.y )
		{
			data.waitingType = igl::texture::AWAIT_CENTERED_POS;
			igl::texture::processCenteredPositions(data, lineStream);
		}
	}
}

void igl::texture::processCenteredPositions(igl::texture::Description& data, std::istringstream& lineStream)
{
	igl::texture::processXCenterPosition(data, lineStream, data.position);
	igl::texture::processYCenterPosition(data, lineStream, data.position);
}

void igl::texture::processXCenterPosition(igl::texture::Description& data, std::istringstream& lineStream, TexturePosition& position)
{
	if( igl::texture::AWAIT_CENTERED_POS == data.waitingType )
	{
		if( lineStream >> data.identifier )
		{
			if( igl::texture::X_CENTER_ID == data.identifier )
			{
				if( !( lineStream >> position.on_x_centered ) )
				{
					throw std::runtime_error{ igl::texture::getErrorMessage(igl::texture::X_CENTER_ID, "on_x_centered texture boolean") };
				}
			}
		}
	}
}

void igl::texture::processYCenterPosition(igl::texture::Description& data, std::istringstream& lineStream, TexturePosition& position)
{
	if( igl::texture::AWAIT_CENTERED_POS == data.waitingType )
	{
		if( lineStream >> data.identifier )
		{
			if( igl::texture::Y_CENTER_ID == data.identifier )
			{
				if( !( lineStream >> position.on_y_centered ) )
				{
					throw std::runtime_error{ igl::texture::getErrorMessage(igl::texture::Y_CENTER_ID, "on_y_centered texture boolean") };
				}
			}
		}
	}
}

std::string igl::texture::getErrorMessage(const std::string& waitingToken, const std::string& expectedThing)
{
	return std::string{"Error: the '" + waitingToken + "' token expected " + expectedThing + " , but reading failed."};
}