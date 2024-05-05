#include "advancedDrawing/interfaceGeneratorLanguage/elementsLoadingFunctions/fontsScriptLoader.h"
#include "logging/logsStruct.h"
#include "advancedDrawing/interfaceGeneratorLanguage/optionsStructs/fontsOptions.h"
#include "advancedDrawing/interfaceGeneratorLanguage/interfaceGeneratorConsts.h"
#include "consts/fontsPaths.h"
#include <sstream>

void igl::font::openScriptFile(AppLogFiles& logs, std::vector< sdl2::Font >& fonts, const std::string& scriptFile, unsigned squareSize)
{
	if( std::ifstream fontDescriptionFile{ scriptFile } )
	{
		igl::font::Description data{scriptFile, squareSize};
		while( std::getline( fontDescriptionFile, data.fileLine ) )
		{
			std::istringstream lineStream{ data.fileLine };
			igl::font::readIdentifier(logs, data, lineStream);
			addFontIfNothingFailed(logs, fonts, data);
			data.fileLineNumber++;
		}
	}
	else{
		logs.error.wrFileOpeningError(scriptFile, "load 'sdl2::Font' description");
	}
}

void igl::font::addFontIfNothingFailed(AppLogFiles& logs, std::vector< sdl2::Font >& fonts, igl::font::Description& data)
{
	if( data.isLoadingPerfect )
	{
		logs.warning << "Adding '" << data.fontPath << "' font with size " << data.fontSize << " from '" << data.scriptFilePath << "' file.\n";
		fonts.emplace_back( sdl2::Font{logs.error, data.fontPath, data.fontSize} );
	}
}

void igl::font::readIdentifier(AppLogFiles& logs, igl::font::Description& data, std::istringstream& lineStream)
{
	while( lineStream >> data.identifier )
	{
		igl::font::appendArialStdPath(data);
		igl::font::appendNeuroFontStdPath(data);
		igl::font::appendCustomPath(logs, data, lineStream);
		igl::font::appendProportionalFontSize(logs, data, lineStream);
		igl::font::appendStaticFontSize(logs, data, lineStream);
	}
}

void igl::font::appendArialStdPath(igl::font::Description& data)
{
	if( data.identifier == igl::font::ArialStandardPath )
	{
		data.fontPath = ArialFontPath;
	}
}

void igl::font::appendNeuroFontStdPath(igl::font::Description& data)
{
	if( data.identifier == igl::font::NeuroFontStandardPath )
	{
		data.fontPath = NeuroFontPath;
	}
}

void igl::font::appendCustomPath(AppLogFiles& logs, igl::font::Description& data, std::istringstream& lineStream)
{
	if( data.identifier == igl::font::FontPath )
	{
		if( !( lineStream >> data.fontPath ) )
		{
			logs.error << "Error: custom font path '" << igl::font::FontPath << "' identifier was read but reading following font custom path failed.\n";
			data.isLoadingPerfect = false;
		}
	}
}

void igl::font::appendProportionalFontSize(AppLogFiles& logs, igl::font::Description& data, std::istringstream& lineStream)
{
	if( data.identifier == igl::font::ProportionalSize )
	{
		unsigned readValue{0};
		if( lineStream >> readValue )
		{
			if( readValue > 0 )
			{
				data.fontSize = readValue * data.squareSize / 64;
			}
			else{
				igl::font::logBadFontSizeValue(logs, data, readValue);
			}
		}
		else{
			logs.error << "Error: couldn't read proportional font size in '" << data.scriptFilePath << "' file at line number " << data.fileLineNumber << " . \n";
			data.isLoadingPerfect = false;
		}
	}
}

void igl::font::appendStaticFontSize(AppLogFiles& logs, igl::font::Description& data, std::istringstream& lineStream)
{
	if( data.identifier == igl::font::StaticSize )
	{
		unsigned readValue{0};
		if( lineStream >> readValue )
		{
			if( readValue > 0 )
			{
				data.fontSize = readValue;
			}
			else{
				igl::font::logBadFontSizeValue(logs, data, readValue);
			}
		}
		else{
			logs.error << "Error: couldn't read proportional font size in '" << data.scriptFilePath << "' file at line number " << data.fileLineNumber << " . \n";
			data.isLoadingPerfect = false;
		}
	}
}

void igl::font::logBadFontSizeValue(AppLogFiles& logs, igl::font::Description& data, unsigned readValue)
{
	logs.error << "Error: bad font size value : " << readValue << " in '" << data.scriptFilePath << "' file at line number " << data.fileLineNumber << " .\n";
	data.isLoadingPerfect = false;
}