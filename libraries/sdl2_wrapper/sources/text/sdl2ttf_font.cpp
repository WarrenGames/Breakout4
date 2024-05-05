#include "text/sdl2ttf_font.h"
#include "logging/logFile.h"
#include <string>

sdl2::Font::Font(LogFile& log, const fs::path& fontPath, unsigned fontSize):
	font{ TTF_OpenFont(fontPath.string().c_str(), fontSize) }
{
	outputAnErrorMessage(log, fontPath);
}

sdl2::Font::operator bool() const
{
	return font != nullptr;
}

TTF_Font* sdl2::Font::get() const
{
	return font.get();
}

void sdl2::Font::reset(LogFile& log, const fs::path& fontPath, unsigned fontSize)
{
	font.reset( TTF_OpenFont(fontPath.string().c_str(), fontSize) );
	outputAnErrorMessage(log, fontPath);
}

void sdl2::Font::outputAnErrorMessage(LogFile& log, const fs::path& fontPath) const
{
	if( nullptr == font )
	{
		log.wrRessourceCreationError("TTF_Font: " + fontPath.string(), TTF_GetError() );
	}
}

void sdl2::Font::reset()
{
	font.reset();
}