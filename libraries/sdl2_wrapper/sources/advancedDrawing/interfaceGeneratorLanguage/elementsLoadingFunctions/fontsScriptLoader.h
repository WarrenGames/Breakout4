#ifndef FONTS_SCRIPT_LOADER_H
#define FONTS_SCRIPT_LOADER_H

#include "text/sdl2ttf_font.h"
#include <vector>
#include <string>

struct AppLogFiles;

namespace igl{

namespace font{
	struct Description;
	
	void openScriptFile(AppLogFiles& logs, std::vector< sdl2::Font >& fonts, const std::string& scriptFile, unsigned squareSize);
	
	void addFontIfNothingFailed(AppLogFiles& logs, std::vector< sdl2::Font >& fonts, igl::font::Description& data);
	
	void readIdentifier(AppLogFiles& logs, igl::font::Description& data, std::istringstream& lineStream);
	
	void appendArialStdPath(igl::font::Description& data);
	
	void appendNeuroFontStdPath(igl::font::Description& data);
	
	void appendCustomPath(AppLogFiles& logs, igl::font::Description& data, std::istringstream& lineStream);
	
	void appendProportionalFontSize(AppLogFiles& logs, igl::font::Description& data, std::istringstream& lineStream);
	
	void appendStaticFontSize(AppLogFiles& logs, igl::font::Description& data, std::istringstream& lineStream);
	
	void logBadFontSizeValue(AppLogFiles& logs, igl::font::Description& data, unsigned readValue);
}

}

#endif //FONTS_SCRIPT_LOADER_H