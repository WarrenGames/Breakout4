#include "advancedDrawing/interfaceGeneratorLanguage/elementsLoadingFunctions/textsBlocksComponent.h"
#include "logging/logsStruct.h"
#include "advancedDrawing/interfaceGeneratorLanguage/interfaceGeneratorConsts.h"
#include <sstream>
#include <algorithm>
#include <cassert>

igl::TextsConfigElements::TextsConfigElements(const std::string& configFilePath):
	filePath{ configFilePath },
	fileLineNumber{1},
	expectedLines{0}
{
	
}

igl::Texts::Texts(AppLogFiles& logs, const std::string& configFilePath):
	isLoadingPerfect{true}
{
	if( std::ifstream configFile{ configFilePath } )
	{
		igl::TextsConfigElements config{configFilePath};
		while( std::getline( configFile, config.fileLine ) )
		{
			std::istringstream lineStream{ config.fileLine };
			readData(logs, lineStream, config);
			config.fileLineNumber++;
		}
	}
}

igl::Texts::operator bool() const
{
	return isLoadingPerfect;
}

const std::string& igl::Texts::getText(std::size_t fileIndex, std::size_t lineIndex) const
{
	assert( fileIndex < texts.size() );
	assert( lineIndex < texts[fileIndex].size() );
	return texts[fileIndex][lineIndex];
}

std::size_t igl::Texts::size() const
{
	return texts.size();
}

std::size_t igl::Texts::lineNumber(std::size_t index) const
{
	assert( index < texts.size() );
	return texts[index].size();
}

void igl::Texts::readData(AppLogFiles& logs, std::istringstream& lineStream, igl::TextsConfigElements& elements)
{
	if( lineStream >> elements.identifier >> elements.path )
	{
		if( elements.identifier == igl::objId::TextsBlocksId )
		{
			if( lineStream >> elements.expectedLines )
			{
				texts.emplace_back( TextsBlocks{logs.error, elements.path, elements.expectedLines} );
			}
			else{
				texts.emplace_back( TextsBlocks{logs.error, elements.path} );
			}
		}
		else{
			logs.error << "Error: bad identifier: " << elements.identifier << " at line number " << elements.fileLineNumber << " of '" << elements.filePath << "' file.\n";
			isLoadingPerfect = false;
		}
	}
	else{
		logs.error.wrReadErrorMessage(elements.filePath, "texts blocks data for 'interface generator language'");
		isLoadingPerfect = false;
	}
}